#include <Arduino.h>
#include <time.h>
#include <sys/time.h>
// #include <esp_bt.h>
// #include <esp_bt_main.h>
// #include <esp_wifi.h>
// #include <SPI.h>
// #include <SD.h>
#include <Wire.h>

#include "device.h"
#include "scheduler.h"
#include "sensors.h"
#include "myutils.h"
#include "sigfox.h"
#include "LinkedList.h"
#include "datalogger.h"
#include "rtcmodule.h"


#ifdef UPDATE_RTC
#include "unixtime.h"
#endif

#define LED_TEST 13
#define START_BUTTON 34
#define SIGFOX_WAKEUP_PIN 12
#define SIGFOX_RESET_PIN 14

RTC_DATA_ATTR int boot_count = 0;
RTC_DATA_ATTR SchedTask tasks[10];
RTC_DATA_ATTR Device module;
RTC_DATA_ATTR NetworkDevice mySigfox;
RTC_DATA_ATTR LinkedList<DataItemList*> dataValues = LinkedList<DataItemList*>();
RTC_DATA_ATTR payload payload_data;

#define MAX_SENSORS 5
#define MAX_PERIOD 86400        // period 24h in seconds


// #define SLEEPMODE
#define uS_TO_S_FACTOR 1000000      /* Conversion factor for micro seconds to seconds */
#define TIME_TO_SLEEP  10           /* Time ESP32 will go to sleep (in seconds) */


void setup(){
    pinMode(LED_TEST,OUTPUT);                       // Test led. Waiting message sigfox
    digitalWrite(LED_TEST, LOW);
    
    pinMode(SIGFOX_WAKEUP_PIN, INPUT_PULLUP);              // Pin wake up Sigfox
    // pinMode(SIGFOX_RESET_PIN, INPUT_PULLUP);              // Pin wake up Sigfox

    // START BUTTON *************************
    pinMode(START_BUTTON, INPUT);
    while( !digitalRead(START_BUTTON) ){
    }
    Serial.println("STARTING PROGRAM!\n");
    delay(500);
    // **************************************

    #ifdef DEBUG
        Serial.begin(115200);
        while(!Serial);
    #endif
    Wire.begin();
    mySigfox.begin();
    
    mySigfox.resetDevice();

    #ifdef UPDATE_RTC
        updateRTC();
    #endif

    // Serial.print("PAYLOAD SIZE: "); Serial.println(sizeof(payload));

    

    //***** TURN OFF WIFI/BLUETOOTH **********// NEED CHECK IF ALWAYS OR JUST ON BOOT MENU
    // esp_bluedroid_disable();
    // esp_bluedroid_deinit();
    // esp_bt_controller_disable();
    // esp_bt_controller_deinit();
    // esp_bt_mem_release(ESP_BT_MODE_BTDM);
    // esp_wifi_stop();
    // esp_wifi_deinit();
    

    // ************************ROUTINE TO RUN ONLY ON SYSTEM BOOT *************************
    if(!boot_count){

        Serial.println(getDate());
        if( mySigfox.ready() ){
            #ifdef DEBUG
                Serial.println("Sigfox is ready!");
                Serial.println("main():ID: " + mySigfox.getID());
                Serial.println("main():PAC: " + mySigfox.getPAC());
            #endif
        }else{
            #ifdef DEBUG
                Serial.println("Sigfox is NOT ready!");
            #endif
        }

        // mySigfox.send(&payload_data, sizeof(payload));

        newLogFile("/log/datalogger.txt");
        newLogFile("/log/logTemp.txt");
        newLogFile("/log/logPh.txt");
        newLogFile("/log/logDo.txt");
        newLogFile("/log/logCond.txt");

        // 1. CONFIG init, sensors...
        module.setConfiguration();
        module.setSensors();

        #ifdef DEBUG
            Serial.print("ID: ");
            Serial.println(module.get_id());
            Serial.print("Location: ");
            Serial.println(module.get_location());
            Serial.print("Number of Sensors: ");
            Serial.println(module.get_nSensors());
        #endif

        // 2. Calculate LCM (least comun multiplier) to configure periodical wakeup


        Sched_Init();

        // HERE ADD FUNCTIONS OF READING SENSORS
        Sched_AddT(readTemp, module.connectedSensors[0]->get_period());
        Sched_AddT(readPh, module.connectedSensors[1]->get_period());

        boot_count = 1;
    }
    // ************************************************************************************
}

void loop(){

    // 1- SET NEXT SENSOR INTERRUP
    Sched_Schedule();

    // 2- RUN THIS READ TASK CYCLE
    Sched_Dispatch();

    // 3- PROCESS THIS DATA CYCLE


    // 4- SAVE THIS DATA CYCLE
    logData();
    // 5- CHECK ALARMS

    // 6- SIGFOX COMMUNICATION

    // 7- DEEPSLEEP

    unsigned long time_next_read = MAX_PERIOD;
    for(uint8_t i=0; i<10; i++){
        if(!tasks[i].func){
            if(tasks[i].nextExec < time_next_read){
                time_next_read = tasks[i].nextExec;
            }
        }
    }

    Serial.print("Next execution: "); Serial.println(time_next_read);

    #ifdef SLEEPMODE
        // BEFORE GO SLEEP, CALCULATE TIME_TO_SLEEP!!!!!!!!!!!!!!!
        esp_sleep_enable_timer_wakeup(TIME_TO_SLEEP * uS_TO_S_FACTOR);
        esp_deep_sleep_start();
    #endif
    // 8- WAIT NEXT INTERRUPT
    #ifndef SLEEPMODE
        delay(1000);
    #endif
}


    // time_t tt = time(NULL);
    // date = *gmtime(&tt);//Converte o tempo atual e atribui na estrutura
    // char date_format[64];
	// strftime(date_format, 64, "%d/%m/%Y %H:%M:%S", &date);//Cria uma String formatada da estrutura "data"

	// time_t tt = time(NULL);//Obtem o tempo atual em segundos. Utilize isso sempre que precisar obter o tempo atual
	// data = *gmtime(&tt);//Converte o tempo atual e atribui na estrutura
 
		
	// 	char data_formatada[64];
	// 	strftime(data_formatada, 64, "%d/%m/%Y %H:%M:%S", &data);//Cria uma String formatada da estrutura "data"
 
 
	// 	printf("\nUnix Time: %d\n", int32_t(tt));//Mostra na Serial o Unix time
	// 	printf("Data formatada: %s\n", data_formatada);//Mostra na Serial a data formatada
 
 
 
 
// 		/*
// 			Com o Unix time, podemos facilmente controlar acoes do MCU por data, visto que utilizaremos os segundos
// 			e sao faceis de usar em IFs
 
// 			Voce pode criar uma estrutura com a data desejada e depois converter para segundos (inverso do que foi feito acima)
// 			caso deseje trabalhar para atuar em certas datas e horarios
 
// 			No exemplo abaixo, o MCU ira printar o texto **APENAS** na data e horario (28/02/2019 12:00:05) ate (28/02/2019 12:00:07)
// 		*/
// 		if (tt >= 1551355205 && tt < 1551355208)//Use sua data atual, em segundos, para testar o acionamento por datas e horarios
// 		{
// 			printf("Acionando carga durante 3 segundos...\n");
// 		}
// 	}
 
	
// }
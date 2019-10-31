#include <Arduino.h>
#include <time.h>
#include <sys/time.h>
#include <esp_bt.h>
#include <esp_bt_main.h>
#include <esp_wifi.h>
#include <SPI.h>
#include <SD.h>

#include "device.h"
#include "scheduler.h"
#include "sensors.h"
#include "filemanager.h"

RTC_DATA_ATTR int boot_count = 0;
RTC_DATA_ATTR SchedTask tasks[10];
RTC_DATA_ATTR Device module;

#define uS_TO_S_FACTOR 1000000  /* Conversion factor for micro seconds to seconds */
#define TIME_TO_SLEEP  10        /* Time ESP32 will go to sleep (in seconds) */

File myFile;

void setup(){
    //***** TURN OFF WIFI/BLUETOOTH **********//
    // esp_bluedroid_disable();
    // esp_bluedroid_deinit();
    // esp_bt_controller_disable();
    // esp_bt_controller_deinit();
    // esp_bt_mem_release(ESP_BT_MODE_BTDM);
    // esp_wifi_stop();
    // esp_wifi_deinit();


    // 1. CONFIG init, sensors...
    // 2. Calculate LCM (least comun multiplier) to configure periodical interrupt

    Serial.begin(115200);
    while(!SD.begin(SS));
    myFile = SD.open("/config.xml");
    if(myFile){
        while(myFile.available()){
            Serial.print(myFile.read());
            Serial.print("\n");
        }
    }

    // ************************ROUTINE TO RUN ONLY ON SYSTEM BOOT *************************
    if(!boot_count){
        module.setConfiguration();
        Serial.print("ID: ");
        Serial.println(module.get_id());
        Serial.print("location: ");
        Serial.println(module.get_location());

        Sched_Init();
        Sched_AddT(func1, 10);
        Sched_AddT(func2, 20);
        Sched_AddT(func3, 30);
        Sched_AddT(func4, 40);
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
    // 5- CHECK ALARMS
    // 6- SIGFOX COMMUNICATION
    // 7- DEEPSLEEP
    // 8- WAIT NEXT INTERRUPT

	// BEFORE GO SLEEP, CALCULATE SLEEPING TIME!!!!!!!!!!!!!!!
    // esp_sleep_enable_timer_wakeup(TIME_TO_SLEEP * uS_TO_S_FACTOR);
    // esp_deep_sleep_start();
    delay(10000);
}

// struct tm date;
    // time_t tt = time(NULL);
    // date = *gmtime(&tt);//Converte o tempo atual e atribui na estrutura
    // char date_format[64];
	// strftime(date_format, 64, "%d/%m/%Y %H:%M:%S", &date);//Cria uma String formatada da estrutura "data"

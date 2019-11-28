#include <Arduino.h>
// #include <time.h>
// #include <sys/time.h>
// #include <esp_bt.h>
// #include <esp_bt_main.h>
// #include <esp_wifi.h>
// #include <SPI.h>
// #include <SD.h>
// #include <Wire.h>
// #include <Adafruit_ADS1015.h>

#include "device.h"
#include "scheduler.h"
// #include "sensors.h"
// #include "filemanager.h"
#include "utils.h"
#include "sigfox.h"
// #include "IO_WSSFM10.h"
// #include "wisol_sigfox.h"

#define DEBUG
#define LED_TEST 13
#define START_BUTTON 34
#define WAKEUP_PIN 12

// #define SLEEPMODE
#define MAX_SENSORS 5

RTC_DATA_ATTR int boot_count = 0;
RTC_DATA_ATTR SchedTask tasks[10];
RTC_DATA_ATTR Device module;
RTC_DATA_ATTR SensorValues lastReads;
NetworkDevice mySigfox;

#define uS_TO_S_FACTOR 1000000  /* Conversion factor for micro seconds to seconds */
#define TIME_TO_SLEEP  10        /* Time ESP32 will go to sleep (in seconds) */

void setup(){
    pinMode(LED_TEST,OUTPUT);
    digitalWrite(LED_TEST, LOW);
    pinMode(START_BUTTON, INPUT);
    pinMode(WAKEUP_PIN, INPUT_PULLUP);

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

    #ifdef DEBUG
        Serial.begin(115200);
    #endif

    mySigfox.begin();

    while( !digitalRead(START_BUTTON) ){
    }
    Serial.println("STARTING PROGRAM!\n");
    delay(500);

    if(mySigfox.ready()){
        Serial.println("Sigfox is ready!");
        Serial.println("ID: " + mySigfox.getID());
        Serial.println("PAC: " + mySigfox.getPAC());

        Serial.print("Entering in sleep mode... ");
        mySigfox.deepSleep();
        Serial.println("Sleeping...");
        delay(5000);
        Serial.println("Wake up from sleep!");
        mySigfox.wakeUpDeepSleep();
    }else{
        Serial.println("Sigfox is NOT ready!");
    }

    // ************************ROUTINE TO RUN ONLY ON SYSTEM BOOT *************************
    if(!boot_count){

        module.setConfiguration();
        module.setSensors();
        Serial.print("ID: ");
        Serial.println(module.get_id());
        Serial.print("Location: ");
        Serial.println(module.get_location());
        Serial.print("Number of Sensors: ");
        Serial.println(module.get_nSensors());

        Sched_Init();

        //Sched_AddT(module.connectedSensors[1]->Sensor::readSensor, module.connectedSensors[1]->get_period());
        
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

    module.temperatureSensor.readSensor();

    Serial.println("ID: " + mySigfox.getID());

    #ifdef SLEEPMODE
        // BEFORE GO SLEEP, CALCULATE TIME_TO_SLEEP!!!!!!!!!!!!!!!
        esp_sleep_enable_timer_wakeup(TIME_TO_SLEEP * uS_TO_S_FACTOR);
        esp_deep_sleep_start();
    #endif
    #ifndef SLEEPMODE
        delay(1000);
    #endif
}

// struct tm date;
    // time_t tt = time(NULL);
    // date = *gmtime(&tt);//Converte o tempo atual e atribui na estrutura
    // char date_format[64];
	// strftime(date_format, 64, "%d/%m/%Y %H:%M:%S", &date);//Cria uma String formatada da estrutura "data"

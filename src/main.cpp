#include <Arduino.h>
#include <time.h>
#include <sys/time.h>
#include <esp_bt.h>
#include <esp_bt_main.h>
#include <esp_wifi.h>

#include "scheduler.h"
//#include "sensors.h"

RTC_DATA_ATTR int boot_count = 0;
RTC_DATA_ATTR Sched_Task_t Tasks_struct_RTC[10];

#define uS_TO_S_FACTOR 1000000  /* Conversion factor for micro seconds to seconds */
#define TIME_TO_SLEEP  10        /* Time ESP32 will go to sleep (in seconds) */

struct tm date;

void func1(){
    Serial.println("print FUNC_1");
}

void func2(){
    Serial.println("print FUNC_2");
}

void func3(){
    Serial.println("print FUNC_3");
}

void func4(){
    Serial.println("print FUNC_4");
}

void setup(){
    // delay(5000);
    // esp_bluedroid_disable();
    // esp_bluedroid_deinit();
    // esp_bt_controller_disable();
    // esp_bt_controller_deinit();
    // esp_bt_mem_release(ESP_BT_MODE_BTDM);
    // esp_wifi_stop();
    // esp_wifi_deinit();

    copy_struct_to(Tasks_struct_RTC, Tasks);

    // 1. CONFIG init, sensors...
    // 2. Calculate LCM (least comun multiplier) to configure periodical interrupt

    Serial.begin(115200);

    // timeval tv;                         // Cria a estrutura temporaria para funcao abaixo.
	// tv.tv_sec = 697593600;              // Set actual date in UNIX 
	// settimeofday(&tv, NULL);            // Configura o RTC para manter a data atribuida atualizada.

    if(!boot_count){
        Sched_Init();           // periodic task
        Sched_AddT(func1, 10);
        Sched_AddT(func2, 20);
        Sched_AddT(func3, 30);
        Sched_AddT(func4, 40);
        boot_count = 1;
    }
	
}

void loop(){

    // 1- SET NEXT SENSOR INTERRUP
    // 2- RUN THIS READ TASK CYCLE
    // 3- PROCESS THIS DATA CYCLE
    // 4- SAVE THIS DATA CYCLE
    // 5- CHECK ALARMS
    // 6- SIGFOX COMMUNICATION
    // 7- DEEPSLEEP
    // 8- WAIT NEXT INTERRUPT

    // time_t tt = time(NULL);
    // date = *gmtime(&tt);//Converte o tempo atual e atribui na estrutura
    // char date_format[64];
	// strftime(date_format, 64, "%d/%m/%Y %H:%M:%S", &date);//Cria uma String formatada da estrutura "data"
 

    Sched_Schedule();
    Sched_Dispatch();

    copy_struct_to(Tasks, Tasks_struct_RTC);
    esp_sleep_enable_timer_wakeup(TIME_TO_SLEEP * uS_TO_S_FACTOR);
    esp_deep_sleep_start();
}
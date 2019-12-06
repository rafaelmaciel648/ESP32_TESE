#include "rtcmodule.h"
// #include <WiFi.h>
#include <sys/time.h>
#include <time.h>
#include <Wire.h>
#include "myutils.h"

#ifdef UPDATE_RTC
#include "unixtime.h"
#endif


#define DS1307_I2C_ADDRESS 0x68


// Convert normal decimal numbers to binary coded decimal
byte decToBcd(byte val){
    return( (val/10*16) + (val%10) );
}
// Convert binary coded decimal to normal decimal numbers
byte bcdToDec(byte val){
    return( (val/16*10) + (val%16) );
}

void setDS1307time(byte second, byte minute, byte hour, byte dayOfWeek, byte dayOfMonth, byte month, byte year){
    // sets time and date data to DS1307
    Wire.beginTransmission(DS1307_I2C_ADDRESS);
    Wire.write(0); // set next input to start at the seconds register
    Wire.write(decToBcd(second)); // set seconds
    Wire.write(decToBcd(minute)); // set minutes
    Wire.write(decToBcd(hour)); // set hours
    Wire.write(decToBcd(dayOfWeek)); // set day of week (1=Sunday, 7=Saturday)
    Wire.write(decToBcd(dayOfMonth)); // set date (1 to 31)
    Wire.write(decToBcd(month)); // set month
    Wire.write(decToBcd(year)); // set year (0 to 99)
    Wire.endTransmission();
}

void readDS1307time(byte *second, byte *minute, byte *hour, byte *dayOfWeek, byte *dayOfMonth, byte *month, byte *year){
    Wire.beginTransmission(DS1307_I2C_ADDRESS);
    Wire.write(0); // set DS1307 register pointer to 00h
    Wire.endTransmission();
    Wire.requestFrom(DS1307_I2C_ADDRESS, 7);
    // request seven bytes of data from DS1307 starting from register 00h
    *second = bcdToDec(Wire.read() & 0x7f);
    *minute = bcdToDec(Wire.read());
    *hour = bcdToDec(Wire.read() & 0x3f);
    *dayOfWeek = bcdToDec(Wire.read());
    *dayOfMonth = bcdToDec(Wire.read());
    *month = bcdToDec(Wire.read());
    *year = bcdToDec(Wire.read());
}

#ifdef UPDATE_RTC
void updateRTC(){
    struct tm date;
    time_t time = unixtime();
    date = *gmtime(&time);

    setDS1307time(  (uint8_t)date.tm_sec,
                    (uint8_t)date.tm_min,
                    (uint8_t)date.tm_hour,
                    (uint8_t)date.tm_wday + 1,
                    (uint8_t)date.tm_mday,
                    (uint8_t)date.tm_mon + 1,
                    (uint8_t)date.tm_year % 100
    );

    return;
}
#endif

String getCurrentTime(){
    byte second, minute, hour, dayOfWeek, dayOfMonth, month, year;
    // retrieve data from DS1307
    readDS1307time(&second, &minute, &hour, &dayOfWeek, &dayOfMonth, &month, &year);

    struct tm date;
    date.tm_sec = second;
    date.tm_min = minute;
    date.tm_hour = hour;
    date.tm_wday = dayOfWeek - 1;
    date.tm_mday = dayOfMonth;
    date.tm_mon = month - 1;
    date.tm_year = year + 100;

    char date_format[30];
	strftime(date_format, 30, "%d/%m/%Y , %H:%M:%S", &date);

    String date_string = String(date_format);
    return date_string;
}

String getDate(){
    byte second, minute, hour, dayOfWeek, dayOfMonth, month, year;
    // retrieve data from DS1307
    readDS1307time(&second, &minute, &hour, &dayOfWeek, &dayOfMonth, &month, &year);

    struct tm date;
    date.tm_sec = second;
    date.tm_min = minute;
    date.tm_hour = hour;
    date.tm_wday = dayOfWeek - 1;
    date.tm_mday = dayOfMonth;
    date.tm_mon = month - 1;
    date.tm_year = year + 100;

    char date_format[45];
	strftime(date_format, 45, "%A, %e %B %Y, %H:%M:%S", &date);

    String date_string = String(date_format);
    return date_string;
}
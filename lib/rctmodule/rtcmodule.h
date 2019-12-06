/* RTCMODULE_H */

#ifndef RTCMODULE_H
#define RTCMODULE_H

#include <Arduino.h>

#ifdef __cplusplus
extern "C" {
#endif

byte decToBcd(byte val);

byte bcdToDec(byte val);

void setDS1307time(byte second, byte minute, byte hour, byte dayOfWeek, byte dayOfMonth, byte month, byte year);

void readDS1307time(byte *second, byte *minute, byte *hour, byte *dayOfWeek, byte *dayOfMonth, byte *month, byte *year);

void updateRTC();

String getDate();

#ifdef __cplusplus
}
#endif

#endif
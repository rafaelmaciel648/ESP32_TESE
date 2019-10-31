/* FILEMANAGER_H */

#ifndef FILEMANAGER_H
#define FILEMANAGER_H

//#include <Arduino.h>
#include <SPI.h>
#include <SD.h>

#ifdef __cplusplus
extern "C" {
#endif

String findParamInFile(const char* param, String filename);


#ifdef __cplusplus
}
#endif

#endif
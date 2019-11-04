/* FILEMANAGER_H */

/* Library to manage access to the files in SD card */


#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include <Arduino.h>
#include <SPI.h>
#include <SD.h>

#ifdef __cplusplus
extern "C" {
#endif

/*
*   Get the tag value of a XML file
*   Parameters:
*       param -> pointer to the tag to be searched
*       file -> file string
*   Return:
*       String of tag value
*/
String getParam(const char* param, String file);

/*
*   Get the tag value of a XML file in position i
*   Parameters:
*       param -> pointer to the tag to be searched
*       file -> file string
*       i -> the indice of the menber tag
*   Return:
*       String of tag value
*/
String getParamInIndice(const char* param, String file, int i);

/*
*   Read a XML file
*   Parameters:
*       filename -> filename to be read (include folder path)
*   Return:
*       String with the content of the file
*/
String readFile(String filename);

#ifdef __cplusplus
}
#endif

#endif
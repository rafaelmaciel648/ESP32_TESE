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

/**
 * Get the tag value of a XML file
 * @param param - pointer to the tag to be searched
 * @param file - file string
 * @return String of tag value
 */
String getParam(const char* param, String file);

/**
 * Get the tag value of XML file in position i
 * @param param - pointer to the tag to be searched
 * @param file - file string
 * @param i - the indice of the menber tag
 * @return String of tag value
 */
String getParamInIndice(const char* param, String file, int i);

/**
 * Read a XML file
 * @param filename - filename to be read (include folder path)
 * @return String with the content of the file
*/
String readFile(String filename);

bool writeFile(String filename, String toWrite);

bool createBlankFile(String filename);

#ifdef __cplusplus
}
#endif

#endif
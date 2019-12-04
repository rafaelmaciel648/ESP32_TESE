/* DATALOGGER_H */

/* Library to log readed data in file */


#ifndef DATALOGGER_H
#define DATALOGGER_H

#include <Arduino.h>

#ifdef __cplusplus
extern "C" {
#endif

void logData(void);

bool newLogFile(String filename);

#ifdef __cplusplus
}
#endif

#endif
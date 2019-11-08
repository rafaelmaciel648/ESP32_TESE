/* UTILS_H */

#ifndef UTILS_H
#define UTILS_H

#include <Arduino.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct{
    double temp = 25.0;
    double ph = 7.0;
    double dissolvedOxygen = 0.0;
    double conductivity = 0.0;
} SensorValues;

#ifdef __cplusplus
}
#endif

#endif
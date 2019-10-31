/* DEVICE_H */

#ifndef DEVICE_H
#define DEVICE_H

#include <Arduino.h>
#include "sensors.h"

#define MAX_SENSORS 5

#ifdef __cplusplus
extern "C" {
#endif

// struct moduleInfo{
//     String id;
//     String gpsLocation;
// };

void setConfiguration();

class Device{
    public:
        String id;
        String gpsLocation;
        Sensor connectedSensors[MAX_SENSORS];

        void setConfiguration();

        String get_id();

        String get_location();
        
};

#ifdef __cplusplus
}
#endif

#endif
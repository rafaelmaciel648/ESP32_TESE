/* DEVICE_H */

#ifndef DEVICE_H
#define DEVICE_H

#include <Arduino.h>
#include "sensors.h"

#define MAX_SENSORS 5

#ifdef __cplusplus
extern "C" {
#endif

/*
*   Device class
*/
class Device{
    public:
        String id;                              // Device ID
        String gpsLocation;                     // Device location
        int nSensors;                           // Number of connected sensors
        Sensor* connectedSensors[MAX_SENSORS];   // Connected Sensors
        TempSensor temperatureSensor;
        PhSensor phSensor;
        // DissolvedOxygenSensor doSensor;
        // ConductivitySensor conductivitySensor;

        /*
        *   Set the configuration of the device from settings in the 'config.xml' file
        * */
        void setConfiguration();

        /*
        *   Set the sensors connected to the device
        * */
        void setSensors();

        /* Getters functions */
        String get_id();
        String get_location();
        int get_nSensors();
        
};

#ifdef __cplusplus
}
#endif

#endif
/* DEVICE_H */

#ifndef DEVICE_H
#define DEVICE_H

#include <Arduino.h>
#include <Adafruit_ADS1015.h>
#include "sensors.h"

#define MAX_SENSORS 5

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Device CLASS
 * 
 */ 
class Device{
    public:
        String id;                              // Device ID
        String gpsLocation;                     // Device location
        int nSensors;                           // Number of connected sensors
        // Adafruit_ADS1115 adc_converter;
        Sensor* connectedSensors[MAX_SENSORS];  // Connected Sensors
        TempSensor temperatureSensor;           // Temperature sensor object
        PhSensor phSensor;                      // PH sensor object
        // DissolvedOxygenSensor doSensor;
        // ConductivitySensor conductivitySensor;

/**
 * Set the configuration of the device from settings in the 'config.xml' file
*/
        void setConfiguration();

/**
 * Set the sensors connected to the device
*/
        void setSensors();

        double readTemperature();
        double readPH();
        // double readDissolvedOxygen();
        // double readConductivity();

/**
 * Getters functions
*/
        String get_id();
        String get_location();
        int get_nSensors();
        
};

#ifdef __cplusplus
}
#endif

#endif
/* SENSORS_H */

#ifndef SENSORS_H
#define SENSORS_H

#include <Arduino.h>

#ifdef __cplusplus
extern "C" {
#endif


enum sensorType{
                digital = 1,
                analog = 2
            };
enum parameter{
                temperature = 1,
                ph = 2,
                dissolvedOxygen = 3,
                conductivity = 4
            };

class Sensor{
    protected:
        String id;                  // Sensor string ID
        sensorType type;            // Sensor type (digital/analog)
        double readPeriod;          // Read period in seconds
		parameter param;            // Parameter (temperature, ph, dissolvedOxygen, conductivity)
        uint8_t state;              // State of sensor (state=0 if disconnected; state!=0 if connected)

    public:

        /**
         * Get sensor ID
         * @return String with ID
         */
        String get_id();

        /**
         * Get sensor type
         * @return  1 if sensor DIGITAL
         *          2 if sensor ANALOG
         */
        sensorType get_type();

        /**
         * Get read period of sensor
         * @return  period in seconds
         */
        double get_period();

        /**
         * Get sensor parameter
         * @return  1 if sensor temperature
         *          2 if sensor ph
         *          3 if dissolved oxygen
         *          4 if conductivity
         */
        parameter get_param();

        /**
         * Get state of sensor
         * @return  0 if sensor disconnected
         *          1 if sensor connected and READY
         */
        uint8_t get_state();

        /**
         * Function to read sensor
         */
        virtual void readSensor() = 0;

        /**
         * Debug function to print sensor information
         */
        virtual void printInfo() = 0;
};

class TempSensor: public Sensor{
    public:
        int8_t min_temp;                    // Minimum temperature reading
        int8_t max_temp;                    // Maximum temperature reading
        double beta;                      // Beta value (25/85) in Kelvin
        double nominalTemperature;
        double noLoadResistor;            // No load resistence at nominal temperature
        double resistanceSeries;

        /**
         * Constructors
         */
        TempSensor();
        TempSensor(String id, String type, double period, int8_t min, int8_t max, double beta, double noLoadResistor, double nominalTemperature);
        
        void readSensor();
        void printInfo();

        /**
         * Read the value of sensor
         * @return the value of temperature measured
         */
        double readTemperature();

        /**
         * Convert temperature Celsisus to Kelvin
         * @param temperature in Celsius
         * @return temperatur in Kelvin
         */
        double celsiusToKelvin(double temperature);

        /**
         * Convert temperature Kelvin to Celsisus
         * @param temperature in Kelvin
         * @return temperatur in Celsius
         */
        double KelvinToCelsius(double temperature);

};

class PhSensor: public Sensor{
	public:
		double slope;                       // Slope of the rect in Volts (typical 59.16mV at 25C)
        double isopotencial;                // voltage at 0 PH
		double iso_error;                   // Error at isopotencial 0 PH in Volts
		double impedance;                   // Output impedance at MOhms

        /**
         * Constructors
         */
        PhSensor();
        PhSensor(String id, String type, double period, double slope, double isopotencial, double iso_error, double impedance);
        
        void readSensor();
        void printInfo();

        /**
         * Read the value of sensor
         * @return the value of temperature measured
         */
        double readPH();

};

// class DissolvedOxygenSensor: public Sensor{
// 	public:
// 		double a;
//         DissolvedOxygenSensor();
// };

// class ConductivitySensor: public Sensor{
// 	public:
// 		double a;
//         ConductivitySensor();
// };

void readTemp();

void readPh();


#ifdef __cplusplus
}
#endif

#endif

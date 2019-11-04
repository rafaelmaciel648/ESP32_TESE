/* SENSORS_H */

#ifndef SENSORS_H
#define SENSORS_H

#include <Arduino.h>

#ifdef __cplusplus
extern "C" {
#endif


enum sensorType{digital, analog};
enum parameter{temperature, ph, dissolvedOxygen, conductivity};

class Sensor{
    protected:
        String id;                          // Sensor string ID
        sensorType type;                    // Sensor type (digital/analog)
        double readPeriod;                // Read period in seconds
		parameter param;                    // Parameter (temperature, ph, dissolvedOxygen, conductivity)
        uint8_t state;                      // State of sensor (state=0 if disconnected; state!=0 if connected)

    public:

        String get_id();
        sensorType get_type();
        double get_period();
        parameter get_param();
        uint8_t get_state();

        virtual void readSensor() = 0;
        virtual void printInfo() = 0;
};

class TempSensor: public Sensor{
    public:
        int8_t min_temp;                    // Minimum temperature reading
        int8_t max_temp;                    // Maximum temperature reading
        uint16_t beta;                      // Beta value (25/85) in Kelvin
        uint16_t noLoadResistor;            // No load resistence at 25 celsius
        TempSensor();
        TempSensor(String id, String type, double period, int8_t min, int8_t max, uint16_t beta, uint16_t noLoadResistor);
        
        void readSensor();
        void printInfo();

        /**** Getters ****/
        sensorType get_type();
        String get_id();
        double get_period();
        parameter get_param();
        uint8_t get_state();
};

class PhSensor: public Sensor{
	public:
		double slope;                       // Slope of the rect in Volts (typical 59.16mV at 25C)
        double isopotencial;                // voltage at 0 PH
		double iso_error;                   // Error at isopotencial 0 PH in Volts
		double impedance;                   // Output impedance at MOhms
        PhSensor();
        PhSensor(String id, String type, double period, double slope, double isopotencial, double iso_error, double impedance);
        
        
        void readSensor();
        void printInfo();

        /**** Getters ****/
        String get_id();
        sensorType get_type();
        double get_period();
        parameter get_param();
        uint8_t get_state();
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




void func1();

void func2();

void func3();

void func4();


#ifdef __cplusplus
}
#endif

#endif


// typedef struct tempSensor{
//     String id;
// 	sensorType type;
// 	int readPeriod;
// 	int8_t min_temp;
//     int8_t max_temp;
//     uint16_t beta;
//     uint16_t noLoadResistor;
// };

// typedef struct phSensor{
//     String id;
// 	sensorType type;
// 	int readPeriod;
// 	double isopotencial;
// 	double slope;
// };

// class Sensor{
//     public:
//         String id;
//         sensorType type;
//         int readPeriod;
// };

// class TempSensor: public Sensor{
//     public:
//         int8_t min_temp;
//         int8_t max_temp;
//         uint16_t beta;
//         uint16_t noLoadResistor;
//         TempSensor(String s, sensorType type, int period, int8_t min, int8_t max, uint16_t beta, uint16_t noLoadResistor){
//             this->id = s;
//             this->type = type;
//             this->readPeriod = period;
//             this->min_temp = min;
//             this->max_temp = max;
//             this->beta = beta;
//             this->noLoadResistor;
//         }
// };

// // TempSensor::TempSensor(String s, sensorType type, int period, int8_t min, int8_t max, uint16_t beta, uint16_t noLoadResistor){

// // }


// class PhSensor: public Sensor{
//   public:
//     //ADD specifications
// };

// class DoSensor: public Sensor{
//   public:
//     //ADD specifications
// };

// class CondSensor: public Sensor{
//   public:
//     //ADD specifications
// };


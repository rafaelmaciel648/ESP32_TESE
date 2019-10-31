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
    public:
        String id;                          // Sensor string ID
        sensorType type;                    // Sensor type (digital/analog)
        int readPeriod;                     // Read period in seconds
		parameter param;                    // Parameter (temperature, ph, dissolvedOxygen, conductivity)
};

class TempSensor: public Sensor{
    public:
        int8_t min_temp;                    // Minimum temperature reading
        int8_t max_temp;                    // Maximum temperature reading
        uint16_t beta;                      // Beta value (25/85) in Kelvin
        uint16_t noLoadResistor;            // No load resistence at 25 celsius
        TempSensor(String s, sensorType type, int period, int8_t min, int8_t max, uint16_t beta, uint16_t noLoadResistor);
        double readTemperature();
};

class PhSensor: public Sensor{
	public:
		double slope;                       // Slope of the rect in Volts (typical 59.16mV at 25C)
		double isopotencial;                // Error at isopotencial 0 PH in Volts
		double impedance;                   // Output impedance at MOhms
        PhSensor(String s, sensorType type, int period, double slope, double isopotencial, double impedance);
        double readPh();
};

class DissolvedOxygenSensor: public Sensor{
	public:
		double a;
};

class ConductivitySensor: public Sensor{
	public:
		double a;
};




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


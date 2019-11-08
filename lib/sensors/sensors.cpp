#include "sensors.h"
#include "thermistorNTC.h"
#include "utils.h"
#include "device.h"
#include <Adafruit_ADS1015.h>

extern SensorValues lastReads;
extern Device module;

#define ADCresolution 32767

/*
*
*       CLASS TempSensor
*
*/

/* Default constructor */
TempSensor::TempSensor(){
    this->state = 0;
}

/* Constructor */
TempSensor::TempSensor(String id, String type, double period, int8_t min, int8_t max, uint16_t beta, uint16_t noLoadResistor){
    this->id = id;
    this->state = 1;

    if(type == "digital"){
        this->type = digital;
    }else if(type == "analog"){
        this->type = analog;
    }

	this->readPeriod = period;
	this->param = temperature;
	this->min_temp = min;
	this->max_temp = max;
	this->beta = beta;
	this->noLoadResistor = noLoadResistor;
}

/* Temperature Read Function */
void TempSensor::readSensor(){
    Serial.println("Reading Temperature......................");
    
    if(this->type == digital){
        // READ TEMPERATURE FROM DIGITAL SENSOR 1-WIRE
    }else if(this->type == analog){
        // READ TEMPERATURE FROM ADC
        Thermistor thermometer(10000.0, this->noLoadResistor, 25.0, this->beta);
        lastReads.temp = thermometer.readCelsius();

        Serial.print("TEMP: "); Serial.println(lastReads.temp,5);
        return;
    }else{
        return;
    }
}

/* Temperature Print Function */
void TempSensor::printInfo(){
    Serial.print(   "\n\tID: " + this->id +
                    "\n\tType: " + this->type +
                    "\n\tPeriod: " + this->readPeriod + " second" +
                    "\n\tParam: " + this->param +
                    "\n\tRange: " + this->min_temp + " to " + this->max_temp + " celsius" +
                    "\n\tBeta Value: " + this->beta +
                    "\n\tNo load resistance: " + this->noLoadResistor + " Ohms"
    );
};


/**
 *       CLASS PhSensor
 *
*/

/* Default constructor */
PhSensor::PhSensor(){
    this->state = 0;
}

/* Constructor */
PhSensor::PhSensor(String id, String type, double period, double slope, double isopotencial, double iso_error, double impedance){
    this->id = id;
    this->state = 1;

    if(type == "digital"){
        this->type = digital;
    }else if(type == "analog"){
        this->type = analog;
    }

	this->readPeriod = period;
	this->param = ph;
    this->slope = slope;
    this->isopotencial = isopotencial;
    this->iso_error = iso_error;
    this->impedance = impedance;
}

/* PH Read Function */
/**
 * PH between -7 to 7 (0 to 14)
 * 
 * NERNST EQUATION
 *      pH = E / ( E0 - 2.303 * R * T / F )
 *          @ E - measure voltage
 *          @ E0 - voltage isopotencial
 *          @ R - Ideal Gas Constante
 *          @ F - Faraday Constante
 *          @ T - temperature in Kelvin
*/
void PhSensor::readSensor(){
    const double F = 96485.3329;          // Faraday Constant C/mol
    const double R = 8.314462;            // Ideal Gas Constant (J/Kmol)
    const double T = 0.0;

    Serial.println("Reading PH......................");

    if(this->type == digital){
        // READ PH FROM DIGITAL SENSOR (??)
    }else if(this->type == analog){
        // READ PH FROM ADC
        Adafruit_ADS1115 adc;
	    adc.begin();
	    adc.setGain(GAIN_ONE);
        double voltage;

        switch (adc.getGain()){
            case GAIN_TWOTHIRDS:
                voltage = adc.readADC_SingleEnded(0) * (6.144 / ADCresolution);
            case GAIN_ONE:
                voltage = adc.readADC_SingleEnded(0) * (4.096 / ADCresolution);
            case GAIN_TWO:
                voltage = adc.readADC_SingleEnded(0) * (2.048 / ADCresolution);
            case GAIN_FOUR:
                voltage = adc.readADC_SingleEnded(0) * (1.024 / ADCresolution);
            case GAIN_EIGHT:
                voltage = adc.readADC_SingleEnded(0) * (0.512 / ADCresolution);
            case GAIN_SIXTEEN:
                voltage = adc.readADC_SingleEnded(0) * (0.256 / ADCresolution);
	    };

        lastReads.ph = voltage / ( ( -2.303 * R * T ) / F ) + 7;
        return;
    }else{
        return;
    }
}

/* PH Print Function */
void PhSensor::printInfo(){
    Serial.print(   "\n\tID: " + this->id +
                    "\n\tType: " + this->type +
                    "\n\tPeriod: " + this->readPeriod + " second" +
                    "\n\tParam: " + this->param +
                    "\n\tSlope: " + this->slope + " V/pH" +
                    "\n\tIsopotencial: " + this->isopotencial + " V +/-" + this->iso_error + " V"
                    "\n\tNo load resistance: " + this->impedance + " Ohms"
    );
};

// DissolvedOxygenSensor::DissolvedOxygenSensor(){};
// ConductivitySensor::ConductivitySensor(){};



/******************GETTERS***********************/
String Sensor::get_id(){
    return this->id;
};
sensorType Sensor::get_type(){
    return this->type;
};
double Sensor::get_period(){
    return this->readPeriod;
};
parameter Sensor::get_param(){
    return this->param;
};
uint8_t Sensor::get_state(){
    return this->state;
};


void func1(){
    Serial.println("print FUNC_1");
}

void func2(){
    Serial.println("print FUNC_2");
}

void func3(){
    Serial.println("print FUNC_3");
}

void func4(){
    Serial.println("print FUNC_4");
}

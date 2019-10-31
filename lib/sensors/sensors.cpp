#include "sensors.h"

TempSensor::TempSensor(String s, sensorType type, int period, int8_t min, int8_t max, uint16_t beta, uint16_t noLoadResistor){
    this->id = s;
    this->type = type;
	this->readPeriod = period;
	this->param = temperature;
	this->min_temp = min;
	this->max_temp = max;
	this->beta = beta;
	this->noLoadResistor = noLoadResistor;
}

double TempSensor::readTemperature(){
    if(this->type == digital){
        // READ TEMPERATURE FROM DIGITAL SENSOR 1-WIRE
    }else if(this->type == analog){
        // READ TEMPERATURE FROM ADC
    }else{
        return 0.0;
    }

    return 0.0;
}

PhSensor::PhSensor(String s, sensorType type, int period, double slope, double isopotencial, double impedance){
    this->id = s;
    this->type = type;
	this->readPeriod = period;
	this->param = ph;
    this->slope = slope;
    this->isopotencial = isopotencial;
    this->impedance = impedance;
}

double PhSensor::readPh(){
    return 0.0;
}


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

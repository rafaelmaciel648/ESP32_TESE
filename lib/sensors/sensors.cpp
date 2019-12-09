#include "sensors.h"
#include "myutils.h"
#include "device.h"
#include "LinkedList.h"
#include "rtcmodule.h"
#include <Adafruit_ADS1015.h>
#include <math.h>

extern Device module;
extern LinkedList<DataItemList*> dataValues;

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
TempSensor::TempSensor(String id, String type, double period, int8_t min, int8_t max, double beta, double noLoadResistor, double nominalTemperature){
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
    this->resistanceSeries = noLoadResistor;
    this->nominalTemperature = nominalTemperature;
}

/* Temperature Read Function */
void TempSensor::readSensor(){
    return;
}

/* Temperature Read Function */
double TempSensor::readTemperature(){
    
    if(this->type == digital){
        // READ TEMPERATURE FROM DIGITAL SENSOR 1-WIRE
    }else if(this->type == analog){
        // READ TEMPERATURE FROM ADC

        double voltage;
        double resistanceNTC;
        double inverseKelvin;
        double vRef;

        module.adc_converter.setGain(GAIN_ONE);

        switch ( module.adc_converter.getGain() ){
            case GAIN_TWOTHIRDS:
                voltage = module.adc_converter.readADC_SingleEnded(0) * (6.144 / ADCresolution);
                vRef = module.adc_converter.readADC_SingleEnded(3) * (6.144 / ADCresolution);
                break;
            case GAIN_ONE:
                voltage = module.adc_converter.readADC_SingleEnded(0) * (4.096 / ADCresolution);
                vRef = module.adc_converter.readADC_SingleEnded(3) * (4.096 / ADCresolution);
                break;
            case GAIN_TWO:
                voltage = module.adc_converter.readADC_SingleEnded(0) * (2.048 / ADCresolution);
                vRef = module.adc_converter.readADC_SingleEnded(3) * (2.048 / ADCresolution);
                break;
            case GAIN_FOUR:
                voltage = module.adc_converter.readADC_SingleEnded(0) * (1.024 / ADCresolution);
                vRef = module.adc_converter.readADC_SingleEnded(3) * (1.024 / ADCresolution);
                break;
            case GAIN_EIGHT:
                voltage = module.adc_converter.readADC_SingleEnded(0) * (0.512 / ADCresolution);
                vRef = module.adc_converter.readADC_SingleEnded(3) * (0.512 / ADCresolution);
                break;
            case GAIN_SIXTEEN:
                voltage = module.adc_converter.readADC_SingleEnded(0) * (0.256 / ADCresolution);
                vRef = module.adc_converter.readADC_SingleEnded(3) * (0.256 / ADCresolution);
                break;
            default:
                voltage = 1.0;
                vRef = 1.0;
        };

        resistanceNTC = this->resistanceSeries / ( ( vRef / voltage ) - 1 );
        inverseKelvin = ( 1 / this->celsiusToKelvin(this->nominalTemperature) ) + log( resistanceNTC / this->noLoadResistor ) / this->beta;
        return this->KelvinToCelsius( 1 / inverseKelvin );

    }else{
        return 0.0;
    }
    return 0.0;
}

/* Temperature Print Function */
void TempSensor::printInfo(){
    #ifdef DEBUG
    Serial.print(   "\n\tID: " + this->id +
                    "\n\tType: " + this->type +
                    "\n\tPeriod: " + this->readPeriod + " second" +
                    "\n\tParam: " + this->param +
                    "\n\tRange: " + this->min_temp + " to " + this->max_temp + " celsius" +
                    "\n\tBeta Value: " + this->beta +
                    "\n\tNo load resistance: " + this->noLoadResistor + " Ohms" +
                    "\n\tSeries Resistance: " + this->resistanceSeries + " Ohms" +
                    "\n\tNominal temperature: " + this->nominalTemperature + " Celsius\n"
    );
    #endif
};

double TempSensor::celsiusToKelvin(double temperature){
    return temperature + 273.1;
};

double TempSensor::KelvinToCelsius(double temperature){
    return temperature - 273.1;
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
    const double T = module.temperatureSensor.readTemperature();

    Serial.println("Reading PH......................");

    if(this->type == digital){
        // READ PH FROM DIGITAL SENSOR (??)
    }else if(this->type == analog){
        // READ PH FROM ADC
        Adafruit_ADS1115 adc;
	    adc.begin();
	    adc.setGain(GAIN_ONE);
        double voltage = 0;
        double ph;

        switch (adc.getGain()){
            case 0:
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

        ph = voltage / ( ( -2.303 * R * T ) / F ) + 7;
        return;
    }else{
        return;
    }
}

void PhSensor::printInfo(){
    #ifdef DEBUG
    Serial.print(   "\n\tID: " + this->id +
                    "\n\tType: " + this->type +
                    "\n\tPeriod: " + this->readPeriod + " second" +
                    "\n\tParam: " + this->param +
                    "\n\tSlope: " + this->slope + " V/pH" +
                    "\n\tIsopotencial: " + this->isopotencial + " V +/-" + this->iso_error + " V"
                    "\n\tNo load resistance: " + this->impedance + " Ohms\n"
    );
    #endif
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


void readTemp(){
    double temp;
    DataItemList *data = new DataItemList();
    temp = module.temperatureSensor.readTemperature();          // Read temperature


    data->param = temperature;
    data->value = temp;
    data->timestamp = getCurrentTime();
    dataValues.add(data);

    return;
}

void readPh(){
    double ph_read;
    DataItemList *data = new DataItemList();
    ph_read = random(1,14);         // Read PH


    data->param = ph;
    data->value = ph_read;
    data->timestamp = getCurrentTime();
    dataValues.add(data);

    return;
}

#include "thermistorNTC.h"
#include <math.h>
#include <Adafruit_ADS1015.h>

#define refVoltage 3.3
#define ADCresolution 32767

Thermistor::Thermistor(const double referenceResistance, const double nominalResistance, const double nominalTemperatureCelsius, const double bValue){
	this->referenceResistance = referenceResistance;
	this->nominalResistance = nominalResistance;
	this->nominalTemperature = celsiusToKelvins(nominalTemperatureCelsius);
	this->bValue = bValue;
}

/**
	Reads and returns a temperature in Celsius.
	Reads the temperature in Kelvin,
	converts in Celsius and return it.

	@return temperature in Celsius.
*/
double Thermistor::readCelsius() {
	return kelvinsToCelsius(readKelvin());
}

/**
	Returns a temperature in Kelvin.
	Reads the thermistor resistance,
	converts in Kelvin and return it.

	@return temperature in Kelvin.
*/
double Thermistor::readKelvin() {
	return resistanceToKelvins(readResistance());
}

double Thermistor::resistanceToKelvins(const double resistance) {
	const double inverseKelvin = 1.0 / this->nominalTemperature +
		log(resistance / this->nominalResistance) / this->bValue;
	return (1.0 / inverseKelvin);
}

double Thermistor::readResistance() {
	return this->referenceResistance / (refVoltage / readVoltage() - 1);
}

double Thermistor::readVoltage() {
	Adafruit_ADS1115 adc;
	adc.begin();
	adc.setGain(GAIN_ONE);
	switch (adc.getGain()){
		case GAIN_TWOTHIRDS:
			return adc.readADC_SingleEnded(0) * (6.144 / ADCresolution);
		case GAIN_ONE:
			return adc.readADC_SingleEnded(0) * (4.096 / ADCresolution);
  		case GAIN_TWO:
		  	return adc.readADC_SingleEnded(0) * (2.048 / ADCresolution);
  		case GAIN_FOUR:
			return adc.readADC_SingleEnded(0) * (1.024 / ADCresolution);
  		case GAIN_EIGHT:
			return adc.readADC_SingleEnded(0) * (0.512 / ADCresolution);
  		case GAIN_SIXTEEN:
			return adc.readADC_SingleEnded(0) * (0.256 / ADCresolution);
	};
	return;
}

double Thermistor::celsiusToKelvins(const double celsius) {
	return (celsius + 273.15);
}

double Thermistor::kelvinsToCelsius(const double kelvins) {
	return (kelvins - 273.15);
}

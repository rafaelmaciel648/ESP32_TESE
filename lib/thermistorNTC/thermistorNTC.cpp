#include "thermistorNTC.h"
#include <math.h>

#define ADCresolution 65535

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
	return this->referenceResistance / (ADCresolution / readVoltage() - 1);
}

double Thermistor::readVoltage() {
	// READ VOLTAGE OF ADC
	return 0.0; //analogRead(this->pin);
}

double Thermistor::celsiusToKelvins(const double celsius) {
	return (celsius + 273.15);
}

double Thermistor::kelvinsToCelsius(const double kelvins) {
	return (kelvins - 273.15);
}

/* THERMISTORNTC_H */

#ifndef THERMISTORNTC_H
#define THERMISTORNTC_H

#ifdef __cplusplus
extern "C" {
#endif

class Thermistor{

	private:
		double referenceResistance;		// resistance in voltage divider (Ohms)
		double nominalResistance;		// resistence of NTC at 25C (Ohms)
		double nominalTemperature; 		// in Celsius
		double bValue;					// beta value (25/85)

  	public:
		/*
		Constructor:
			@param referenceResistance - reference resistance
			@param nominalResistance - nominal resistance at a nominal temperature
			@param nominalTemperature - nominal temperature in Celsius
			@param bValue - b-value of a thermistor
		*/
    	Thermistor(double referenceResistance, double nominalResistance, double nominalTemperatureCelsius, double bValue);

		/*
		Reads a temperature in Celsius from the thermistor.
			@return temperature in degree Celsius
		*/
		double readCelsius();

		/*
		Reads a temperature in Kelvin from the thermistor.
			@return temperature in degree Kelvin
		*/
    	double readKelvin();

  	private:
		/*
		Resistance to Kelvin conversion:
			1/K = 1/K0 + ln(R/R0)/B;
			K = 1 / (1/K0 + ln(R/R0)/B);
			Where
			K0 - nominal temperature,
			R0 - nominal resistance at a nominal temperature,
			R - the input resistance,
			B - b-value of a thermistor.

			@param resistance - resistance value to convert
			@return temperature in degree Kelvin
		*/
    	double resistanceToKelvins(double resistance);

		/*
		Calculates a resistance of the thermistor:
			Converts a value of the thermistor sensor into a resistance.
			R = R0 / (ADC / V - 1);
			Where
			R0 - nominal resistance at a nominal temperature,
			ADC - analog port resolution,
			V - current voltage (analog port value).

			@return resistance of the thermistor sensor.
		*/
		double readResistance();

		/*
		Reads a voltage from the thermistor analog port.
			@return thermistor voltage in analog range (0...1023, for Arduino).
		*/
		double readVoltage();

		/*
		Celsius to Kelvin conversion:
			K = C + 273.15

			@param celsius - temperature in degree Celsius to convert
			@return temperature in degree Kelvin
		*/
		double celsiusToKelvins(double celsius);

		/*
		Kelvin to Celsius conversion:
			C = K - 273.15

			@param kelvins - temperature in degree Kelvin to convert
			@return temperature in degree Celsius
		*/
		double kelvinsToCelsius(double kelvins);
};


#ifdef __cplusplus
}
#endif

#endif
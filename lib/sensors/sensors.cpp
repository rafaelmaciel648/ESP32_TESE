#include "sensors.h"

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
    if(this->type == digital){
        // READ TEMPERATURE FROM DIGITAL SENSOR 1-WIRE
    }else if(this->type == analog){
        // READ TEMPERATURE FROM ADC
    }else{
    }

    Serial.println("Reading Temperature......................");
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


/*
*
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
void PhSensor::readSensor(){
    Serial.println("Reading PH......................");
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

#include "device.h"
#include "filemanager.h"

extern Device module;

String Device::get_id(){
    return this->id;
}

String Device::get_location(){
    return this->gpsLocation;
}

int Device::get_nSensors(){
    return this->nSensors;
};

void Device::setConfiguration(){
    const String file = readFile("/config.xml");
    int n = 0;

    this->id = getParam("id", file);
    this->gpsLocation = getParam("location", file);

    for(int aux=0; aux<file.length(); aux++){
        if( file.substring(aux,aux+8) == "<sensor>" ){
            n++;
        }
    }

    this->nSensors = n;
};

void Device::setSensors(){
    const String config = readFile("/config.xml");
    String sensors = getParam("connected_sensors", config);
    String aux;
    String sensorFile;

    for(int i=0; i<this->nSensors; i++){
        aux = getParamInIndice("sensor", sensors, i);
        sensorFile = readFile("/sensors/" + getParam("sensorID", aux) + ".xml");


        if( getParam("param", sensorFile) == "temperature" ){
            // Temperature sensor
            this->temperatureSensor = TempSensor(
                                        getParam("id", sensorFile),
                                        getParam("type", sensorFile),
                                        (double)getParam("read_period", aux).toInt(),
                                        (uint8_t)getParam("min", sensorFile).toInt(),
                                        (uint8_t)getParam("max", sensorFile).toInt(),
                                        (uint16_t)getParam("beta", sensorFile).toInt(),
                                        (uint16_t)getParam("no_load_resistance", sensorFile).toInt()
                                        );
            this->connectedSensors[i] = &this->temperatureSensor;
        }
        else if( getParam("param", sensorFile) == "ph" ){
            // PH sensor
            this->phSensor = PhSensor(
                                        getParam("id", sensorFile),
                                        getParam("type", sensorFile),
                                        (double)getParam("read_period", aux).toInt(),
                                        (double)getParam("slope", sensorFile).toInt(),
                                        (double)getParam("isopotencial", sensorFile).toInt(),
                                        (double)getParam("iso_error", sensorFile).toInt(),
                                        (double)getParam("impedance", sensorFile).toInt()
                                        );
            this->connectedSensors[i] = &this->phSensor;
        }
        else if( getParam("param", sensorFile) == "do" ){
            // Dissolved Oxygen sensor
            // this->phSensor = PhSensor(
            //                             getParam("id", sensorFile),
            //                             getParam("type", sensorFile),
            //                             (uint16_t)getParam("read_period", aux).toInt(),
            //                             (double)getParam("slope", sensorFile).toInt(),
            //                             (double)getParam("isopotencial", sensorFile).toInt(),
            //                             (double)getParam("iso_error", sensorFile).toInt(),
            //                             (double)getParam("impedance", sensorFile).toInt()
            //                             );
            // this->connectedSensors[i] = &this->phSensor;
        }
        else if( getParam("param", sensorFile) == "conductivity" ){
            // Conductivity sensor
            // this->phSensor = PhSensor(
            //                             getParam("id", sensorFile),
            //                             getParam("type", sensorFile),
            //                             (uint16_t)getParam("read_period", aux).toInt(),
            //                             (double)getParam("slope", sensorFile).toInt(),
            //                             (double)getParam("isopotencial", sensorFile).toInt(),
            //                             (double)getParam("iso_error", sensorFile).toInt(),
            //                             (double)getParam("impedance", sensorFile).toInt()
            //                             );
            // this->connectedSensors[i] = &this->phSensor;
        }
        else{
            // ERROR
        }
    }
};




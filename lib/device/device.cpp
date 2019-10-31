#include "device.h"
#include "filemanager.h"

// extern moduleInfo module;
extern Device module;

String Device::get_id(){
    return this->id;
}

String Device::get_location(){
    return this->gpsLocation;
}

void Device::setConfiguration(){
    const char id[] = "<id>";
    const char location[] = "<location>";

    this->id = findParamInFile(id,"/config.xml");
    this->gpsLocation = findParamInFile(location,"/config.xml");
};
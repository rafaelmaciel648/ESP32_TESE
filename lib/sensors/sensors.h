#include <Arduino.h>
#include <string.h>

class sensor{
  public:
    String id;
    sensorType type;
    int readPeriod;
};

class temp_sensor: public sensor{
  public:
    parameter param = temperature;
    //ADD specifications
};

class ph_sensor: public sensor{
  public:
    parameter param = ph;
    //ADD specifications
};

class do_sensor: public sensor{
  public:
    parameter param = dissolvedOxygen;
    //ADD specifications
};

class cond_sensor: public sensor{
  public:
    parameter param = conductivity;
    //ADD specifications
};

enum parameter{temperature, ph, dissolvedOxygen, conductivity};
enum sensorType{digital, analog};
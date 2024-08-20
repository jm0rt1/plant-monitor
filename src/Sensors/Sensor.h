#ifndef SENSOR_H
#define SENSOR_H

#include <ArduinoJson.h>

class Sensor
{
public:
    virtual void begin() = 0;
    virtual bool read(JsonDocument &jsonDoc) = 0;
};

#endif // SENSOR_H

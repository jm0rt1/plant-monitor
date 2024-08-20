#ifndef TEMPERATURE_SENSOR_H
#define TEMPERATURE_SENSOR_H

#include "Sensor.h"

class TemperatureSensor : public Sensor
{
public:
    void begin() override;
    bool read(JsonDocument &jsonDoc) override;

private:
    float getTemperature();
};

#endif // TEMPERATURE_SENSOR_H

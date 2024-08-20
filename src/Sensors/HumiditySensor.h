#ifndef HUMIDITY_SENSOR_H
#define HUMIDITY_SENSOR_H

#include "Sensor.h"

class HumiditySensor : public Sensor
{
public:
    void begin() override;
    bool read(JsonDocument &jsonDoc) override;

private:
    float getHumidity();
};

#endif // HUMIDITY_SENSOR_H

#include "HumiditySensor.h"

void HumiditySensor::begin()
{
    // Initialize the humidity sensor (e.g., setup GPIO, I2C, etc.)
}

bool HumiditySensor::read(JsonDocument &jsonDoc)
{
    float humidity = getHumidity();
    jsonDoc["humidity"] = humidity;
    return true;
}

float HumiditySensor::getHumidity()
{
    return 60.0; // Replace with actual sensor reading
}

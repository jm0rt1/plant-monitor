#include "TemperatureSensor.h"

void TemperatureSensor::begin()
{
    // Initialize the temperature sensor (e.g., setup GPIO, I2C, etc.)
}

bool TemperatureSensor::read(JsonDocument &jsonDoc)
{
    float temperature = getTemperature();
    jsonDoc["temperature"] = temperature;
    return true;
}

float TemperatureSensor::getTemperature()
{
    return 24.5; // Replace with actual sensor reading
}

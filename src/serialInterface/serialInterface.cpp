#include "serialInterface.h"
#include <Arduino.h>
int soil_pin = A0; // AOUT pin on sensor

float readSensorVoltage(int averages)
{
    float sample;
    float filteredResult = 0;
    float raw;
    for (int i = 0; i < averages; i++)
    {
        raw = analogRead(soil_pin);
        sample = raw / 1024.0 * 3.3; // read sensor
        filteredResult += sample;
        delay(10);
    }
    float result = filteredResult / averages;
    return result;
}

String SerialInterface::printTemperature(UnitsTemperatures unit)
{
    float temp = -1000.0;
    String unitStr;
    if (unit == UnitsTemperatures::F)
    {
        temp = mDht->readTemperature(true);
        unitStr = " Deg F";
    }
    else if (unit == UnitsTemperatures::C)
    {
        temp = mDht->readTemperature(false);
        unitStr = " Deg C";
    }
    if (temp != -1000.0)
    {
        String tempFloatStr = String(temp, 2);
        String out = tempFloatStr + unitStr + "\n";
        Serial.print(out);
    }
    else
    {
        Serial.print("NAK");
    }
}
SerialInterface::SerialInterface()
{
    mDht = new DHT(2, DHT11);
    mDht->begin();
}

void SerialInterface::readCommand()
{
    String cmd = "";
    cmd = Serial.readStringUntil('\n');
    String resp = "received" + cmd;
    if (cmd == "on")

    {
        Serial.print(resp);

        digitalWrite(13, HIGH);
    }
    else if (cmd == "off")
    {
        Serial.print(resp);

        digitalWrite(13, LOW);
    }
    else if (cmd == "temp deg f")
    {
        printTemperature(UnitsTemperatures::F);
    }
    else if (cmd == "temp deg c")
    {
        printTemperature(UnitsTemperatures::C);
    }
    else if (cmd == "all sensors")
    {
        onAllSensors();
    }
    else if (cmd == "percent")
    {
        Serial.print("Setting: ");
        String setting = Serial.readStringUntil('\n');
        float val = setting.toFloat();
        setLightPercent(val);
    }
    else if (cmd == "")
    {
        return;
    }
    else
    {
        Serial.print("NAK: CMD Not Accepted\n");
    }
}

void SerialInterface::onGetData()
{
}

void SerialInterface::onAllSensors()
{
    float temp_c = -1000.0;
    float temp_f = -1000.0;
    float humidity = -1000.0;
    float soilVoltage = -1000.0;

    temp_c = mDht->readTemperature(true);
    temp_f = mDht->readTemperature(false);
    humidity = mDht->readHumidity();
    soilVoltage = readSensorVoltage(10);

    String outString = String(temp_c) + "," + String(temp_f) + "," + String(humidity) + "," + String(soilVoltage) + "\n";
    Serial.print(outString);
}

void SerialInterface::setLightPercent(float val)
{
    mLightPercent = val;
}

float SerialInterface::getLightPercent()
{
    return mLightPercent;
}

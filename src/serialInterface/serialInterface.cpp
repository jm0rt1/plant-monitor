#include "serialInterface.h"
#include <Arduino.h>
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
    else if (cmd == "")
    {
        return;
    }
    else
    {
        Serial.print("NAK: CMD Not Accepted\n");
    }
}
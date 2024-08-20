#include <Arduino.h>
#include "SystemController/SystemController.h"

SystemController systemController;

void setup()
{
    Serial.begin(115200);
    pinMode(0, INPUT_PULLUP); // Configure button on GPIO 0 for entering config mode
}

void loop()
{
    systemController.run();
}

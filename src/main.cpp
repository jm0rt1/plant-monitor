#include <Arduino.h>
#include "serialInterface/serialInterface.h"

// put function declarations here:
int myFunction(int, int);
SerialInterface *si = new SerialInterface();
int redPin = 3;
int greenPin = 6;
int bluePin = 5;

void setColor(int redValue, int greenValue, int blueValue)
{
  analogWrite(redPin, redValue);
  analogWrite(greenPin, greenValue);
  analogWrite(bluePin, blueValue);
}

void setup()
{
  Serial.begin(9600);
  analogReference(AR_EXTERNAL); // set the analog reference to 3.3V
  pinMode(13, OUTPUT);
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
}

void loop()
{
  si->readCommand();
  float soilVoltage = readSensorVoltage(10);
  if (soilVoltage < 2)
  {
    setColor(0, 0, 100);
  }
  else if (soilVoltage > 2)
  {
    setColor(171, 20, 7);
  }

  delay(100); // slight delay between readings
}
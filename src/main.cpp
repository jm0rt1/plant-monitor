#include <Arduino.h>
#include "serialInterface/serialInterface.h"

// put function declarations here:
int myFunction(int, int);
SerialInterface *si = new SerialInterface();
int redPin = 3;
int greenPin = 6;
int bluePin = 5;
int soil_pin = A0; // AOUT pin on sensor

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
  // si->readCommand();
  // setColor(0, 0, 255);
  // delay(1000);
  // setColor(0, 255, 0);
  // delay(1000);
  // setColor(255, 0, 0);
  // delay(1000);

  delay(100); // slight delay between readings
}

// put function definitions here:
int myFunction(int x, int y)
{
}

float readSensorVoltage()
{
  Serial.print("Soil Moisture Sensor Voltage: ");
  Serial.print((float(analogRead(soil_pin)) / 1023.0) * 5); // read sensor
  Serial.println(" V");
}
#include <WiFi.h>
#include <WebServer.h>
#include "config.h"

void handleRoot();

void handleSensor();
// Create an instance of the server on port 80
WebServer server(80);

// Sensor pin
const int sensorPin = A0; // Analog pin connected to the sensor

void setup()
{
    Serial.begin(115200);      // Initialize serial communication
    pinMode(sensorPin, INPUT); // Set sensor pin as input

    // Connect to Wi-Fi network
    Serial.print("Connecting to Wi-Fi");
    WiFi.begin(ssid, password);

    // Wait until connected
    while (WiFi.status() != WL_CONNECTED)
    {
        delay(500);
        Serial.print(".");
    }

    // Print the local IP address
    Serial.println("\nConnected to Wi-Fi network.");
    Serial.print("IP Address: ");
    Serial.println(WiFi.localIP());

    // Define routing
    server.on("/", handleRoot);

    server.on("/sensor", handleSensor);

    // Start the server
    server.begin();
    Serial.println("HTTP server started");
}

void loop()
{
    // Handle client requests
    server.handleClient();
}

void handleRoot()
{
    // Read sensor data
    int sensorValue = random();
    Serial.print("Sensor Value: ");
    Serial.println(sensorValue);

    // Create HTTP response
    String response = "Sensor Value: " + String(sensorValue);

    // Send response
    server.send(200, "text/plain", response);
}

void handleSensor()
{
    // Read sensor data
    static int sensorValue = 1;
    sensorValue++;
    Serial.print("Sensor Value: ");
    Serial.println(sensorValue);

    // Create HTTP response
    String response = "Sensor Value: " + String(sensorValue);

    // Send response
    server.send(200, "text/plain", response);
}
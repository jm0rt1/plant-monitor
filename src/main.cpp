#include <WiFi.h>
#include <WebServer.h>
#include "config.h"

void getMACAddress();
void getIPAddress();
void handleRoot();
void handleSerialCommands();
void handleSensor();
// Create an instance of the server on port 80
WebServer server(80);
unsigned long previousMillis = 0;
const long interval = 1000; // Interval to
// Sensor pin
const int sensorPin = A0; // Analog pin connected to the sensor

void setup()
{

    Serial.begin(115200);      // Initialize serial communication
    pinMode(sensorPin, INPUT); // Set sensor pin as input
    delay(1000);
    // Connect to Wi-Fi network
    Serial.print("Connecting to Wi-Fi");
    WiFi.begin(ssid, password);

    // Wait until connected
    int count = 0;
    while (WiFi.status() != WL_CONNECTED)
    {
        delay(500);
        Serial.print(".");
        count++;
        if (count > 5)
        {
            Serial.println("Failed to connect to Wi-Fi with code:" + String(WiFi.status()));
            Serial.println("Scanning for WiFi networks...");
            int numNetworks = WiFi.scanNetworks();

            if (numNetworks == 0)
            {
                Serial.println("No networks found.");
            }
            else
            {
                Serial.print(numNetworks);
                Serial.println(" networks found:");
                for (int i = 0; i < numNetworks; ++i)
                {
                    Serial.print(i + 1);
                    Serial.print(": ");
                    Serial.print(WiFi.SSID(i));
                    Serial.print(" (");
                    Serial.print(WiFi.RSSI(i));
                    Serial.print(" dBm)");
                    Serial.print(" ");
                    Serial.print((WiFi.encryptionType(i) == WIFI_AUTH_OPEN) ? "Open" : "Secured");
                    Serial.println();
                }
            }
            return;
        }
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
    unsigned long currentMillis = millis();
    if (currentMillis - previousMillis >= interval)
    {
        previousMillis = currentMillis;
        handleSerialCommands();
    }
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

void handleSerialCommands()
{
    if (Serial.available() > 0)
    {
        String command = Serial.readStringUntil('\n');

        // Trim any whitespace
        command.trim();

        if (command == "GET_MAC")
        {
            // Get and print the MAC address
            getMACAddress();
        }
        else if (command == "GET_IP")
        {
            // Get and print the IP address
            getIPAddress();
        }
        else
        {
            Serial.println("Unknown command. Use GET_MAC or GET_IP.");
        }
    }
}

void getMACAddress()
{

    String macAddress = WiFi.macAddress();
    Serial.print("MAC Address: ");
    Serial.println(macAddress);
}

void getIPAddress()
{
    IPAddress ipAddress = WiFi.localIP();
    Serial.print("IP Address: ");
    Serial.println(ipAddress);
}

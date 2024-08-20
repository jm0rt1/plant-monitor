#include "WiFiManager.h"

WiFiManagerHandler::WiFiManagerHandler(SecureStorage &storage)
    : _storage(storage)
{
    // You can configure WiFiManager options here if needed
}

bool WiFiManagerHandler::connect()
{
    char ssid[32];
    char password[64];

    if (retrieveCredentials(ssid, sizeof(ssid), password, sizeof(password)))
    {
        // Try to connect with stored credentials
        WiFi.begin(ssid, password);
        if (WiFi.status() == WL_CONNECTED)
        {
            Serial.println("Connected to Wi-Fi using stored credentials");
            Serial.print("IP Address: ");
            Serial.println(WiFi.localIP());
            return true;
        }
    }

    // If connection with stored credentials failed, start WiFiManager
    if (!wifiManager.autoConnect(apName, apPassword))
    {
        Serial.println("Failed to connect and hit timeout");
        return false;
    }

    // If successfully connected, save the new credentials
    saveCredentials(WiFi.SSID().c_str(), WiFi.psk().c_str());

    Serial.println("Connected to Wi-Fi using new credentials");
    Serial.print("IP Address: ");
    Serial.println(WiFi.localIP());
    return true;
}

bool WiFiManagerHandler::retrieveCredentials(char *ssid, size_t ssidLen, char *password, size_t passwordLen)
{
    if (!_storage.getString("wifi_ssid", ssid, ssidLen) || !_storage.getString("wifi_pass", password, passwordLen))
    {
        Serial.println("No stored Wi-Fi credentials found");
        return false;
    }
    return true;
}

void WiFiManagerHandler::saveCredentials(const char *ssid, const char *password)
{
    _storage.saveString("wifi_ssid", ssid);
    _storage.saveString("wifi_pass", password);
    Serial.println("Wi-Fi credentials saved");
}

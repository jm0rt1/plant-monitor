#ifndef WIFI_MANAGER_H
#define WIFI_MANAGER_H

#include <WiFiManager.h>
#include "SecureStorage/SecureStorage.h"

class WiFiManagerHandler
{
public:
    WiFiManagerHandler(SecureStorage &storage);
    bool connect();

private:
    WiFiManager wifiManager;
    SecureStorage &_storage;
    const char *apName = "ESP32_Config";
    const char *apPassword = "password123";

    bool retrieveCredentials(char *ssid, size_t ssidLen, char *password, size_t passwordLen);
    void saveCredentials(const char *ssid, const char *password);
};

#endif // WIFI_MANAGER_H

#ifndef CONFIG_SERVICE_H
#define CONFIG_SERVICE_H

#include <ESPAsyncWebServer.h>
#include "SecureStorage/SecureStorage.h"

class ConfigService
{
public:
    ConfigService(SecureStorage &storage, uint16_t port = 80);
    void begin();
    void handle();

private:
    AsyncWebServer server;
    SecureStorage &secureStorage;

    void handleRoot(AsyncWebServerRequest *request);
    void handleSave(AsyncWebServerRequest *request);
};

#endif // CONFIG_SERVICE_H

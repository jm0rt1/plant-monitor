#ifndef WEB_SERVICE_H
#define WEB_SERVICE_H

#include <ESPAsyncWebServer.h>
#include <ArduinoJson.h>

class WebService
{
public:
    WebService(uint16_t port = 80);
    void begin();
    void onRequestData(std::function<JsonObject(JsonDocument &)> dataCallback);

private:
    AsyncWebServer server;
    std::function<JsonObject(JsonDocument &)> dataCallback;

    void handleLiveDataRequest(AsyncWebServerRequest *request);
};

#endif // WEB_SERVICE_H

#include "ConfigService.h"

ConfigService::ConfigService(SecureStorage &storage, uint16_t port)
    : server(port), secureStorage(storage) {}

void ConfigService::begin()
{
    // Serve the Wi-Fi configuration page
    server.on("/", HTTP_GET, std::bind(&ConfigService::handleRoot, this, std::placeholders::_1));

    // Handle form submission to save SSID and password
    server.on("/save", HTTP_POST, std::bind(&ConfigService::handleSave, this, std::placeholders::_1));

    server.begin();
}

void ConfigService::handleRoot(AsyncWebServerRequest *request)
{
    request->send(SPIFFS, "/wifi_config.html", String(), false);
}

void ConfigService::handleSave(AsyncWebServerRequest *request)
{
    if (request->hasParam("ssid", true) && request->hasParam("password", true))
    {
        String ssid = request->getParam("ssid", true)->value();
        String password = request->getParam("password", true)->value();

        secureStorage.saveString("wifi_ssid", ssid.c_str());
        secureStorage.saveString("wifi_pass", password.c_str());

        request->send(200, "text/html", "Credentials saved! The device will now attempt to connect to the Wi-Fi network.");
    }
    else
    {
        request->send(400, "text/html", "Missing SSID or Password!");
    }
}

void ConfigService::handle()
{
    // Could add any additional logic here if needed
}

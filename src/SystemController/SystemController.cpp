#include "SystemController.h"

SystemController::SystemController()
    : secureStorage(),
      wifiManager(secureStorage),
      otaUpdate(),
      logger("192.168.1.100", 5000),
      webService(80),
      configService(),
      homeKitService()
{

    if (!secureStorage.begin())
    {
        Serial.println("Failed to initialize secure storage");
        return;
    }

    if (shouldEnterConfigMode())
    {
        enterConfigMode();
    }
    else
    {
        if (!wifiManager.connect())
        {
            logger.log("Failed to connect to WiFi");
            enterConfigMode(); // Fall back to configuration mode
            return;
        }

        if (!logger.connect())
        {
            Serial.println("Failed to connect to logging server");
        }

        otaUpdate.begin("esp32-ota", "admin", 3232);

        tempSensor.begin();
        humiditySensor.begin();

        webService.onRequestData(std::bind(&SystemController::getLiveData, this, std::placeholders::_1));
        webService.begin();

        // Initialize HomeKit
    }
}

void SystemController::run()
{
    if (!shouldEnterConfigMode())
    {
        otaUpdate.handle();
    }
    else
    {
        configService.handle();
    }
}

bool SystemController::shouldEnterConfigMode()
{
    return digitalRead(0) == LOW;
}

void SystemController::enterConfigMode()
{
    Serial.println("Entering configuration mode...");

    // WiFiManager automatically creates a captive portal, so no further code is needed here
}

JsonObject SystemController::getLiveData(JsonDocument &jsonDoc)
{
    JsonObject data = jsonDoc.to<JsonObject>();
    tempSensor.read(jsonDoc);
    humiditySensor.read(jsonDoc);
    return data;
}

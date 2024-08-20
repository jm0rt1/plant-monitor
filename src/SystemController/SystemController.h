#ifndef SYSTEM_CONTROLLER_H
#define SYSTEM_CONTROLLER_H

#include "WiFiManager/WiFiManager.h"
#include "OTAUpdate/OTAUpdate.h"
#include "TCPLogger/TCPLogger.h"
#include "WebService/WebService.h"
#include "ConfigService/ConfigService.h"
#include "Sensors/TemperatureSensor.h"
#include "Sensors/HumiditySensor.h"
#include "SecureStorage/SecureStorage.h"

class SystemController
{
public:
    SystemController();
    void run();

private:
    SecureStorage secureStorage;
    WiFiManagerHandler wifiManager;
    OTAUpdate otaUpdate;
    TCPLogger logger;
    WebService webService;
    ConfigService configService;
    HomeKitService homeKitService;

    TemperatureSensor tempSensor;
    HumiditySensor humiditySensor;

    bool shouldEnterConfigMode();
    void enterConfigMode();

    JsonObject getLiveData(JsonDocument &jsonDoc);
};

#endif // SYSTEM_CONTROLLER_H

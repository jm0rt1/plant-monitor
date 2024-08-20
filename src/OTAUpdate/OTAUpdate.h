#ifndef OTA_UPDATE_H
#define OTA_UPDATE_H

#include <ArduinoOTA.h>

class OTAUpdate
{
public:
    void begin(const char *hostname, const char *password, uint16_t port);
    void handle();
};

#endif // OTA_UPDATE_H

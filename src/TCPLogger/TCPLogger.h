#ifndef TCP_LOGGER_H
#define TCP_LOGGER_H

#include <WiFi.h>
#include <WiFiClient.h>

class TCPLogger
{
public:
    TCPLogger(const char *serverIP, uint16_t port);
    bool connect();
    void log(const char *message);

private:
    const char *_serverIP;
    uint16_t _port;
    WiFiClient _client;
};

#endif // TCP_LOGGER_H

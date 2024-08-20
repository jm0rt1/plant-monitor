#include "TCPLogger.h"

TCPLogger::TCPLogger(const char *serverIP, uint16_t port)
    : _serverIP(serverIP), _port(port) {}

bool TCPLogger::connect()
{
    return _client.connect(_serverIP, _port);
}

void TCPLogger::log(const char *message)
{
    if (!_client.connected())
    {
        if (!connect())
        {
            Serial.println("Failed to connect to the logging server");
            return;
        }
    }
    _client.println(message);
}

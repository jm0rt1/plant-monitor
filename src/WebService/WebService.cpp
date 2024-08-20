#include "WebService.h"

WebService::WebService(uint16_t port)
    : server(port) {}

void WebService::begin()
{
    // Serve the index page
    server.on("/", HTTP_GET, [](AsyncWebServerRequest *request)
              { request->send(200, "text/html", R"rawliteral(
            <!DOCTYPE HTML><html>
            <head>
                <title>ESP32 Live Data</title>
                <script>
                    function fetchLiveData() {
                        fetch('/live-data')
                        .then(response => response.json())
                        .then(data => {
                            document.getElementById('liveData').innerText = JSON.stringify(data, null, 2);
                        });
                    }
                    setInterval(fetchLiveData, 1000);
                </script>
            </head>
            <body>
                <h1>ESP32 Live Data</h1>
                <pre id="liveData"></pre>
            </body>
            </html>
        )rawliteral"); });

    // Serve live data
    server.on("/live-data", HTTP_GET, std::bind(&WebService::handleLiveDataRequest, this, std::placeholders::_1));

    server.begin();
}

void WebService::onRequestData(std::function<JsonObject(JsonDocument &)> callback)
{
    dataCallback = callback;
}

void WebService::handleLiveDataRequest(AsyncWebServerRequest *request)
{
    if (dataCallback)
    {
        StaticJsonDocument<200> jsonDoc;
        JsonObject jsonData = dataCallback(jsonDoc);

        String jsonString;
        serializeJson(jsonDoc, jsonString);
        request->send(200, "application/json", jsonString);
    }
    else
    {
        request->send(500, "application/json", "{\"error\":\"No data callback set\"}");
    }
}

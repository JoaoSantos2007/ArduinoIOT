#ifndef SERVER_H
#define SERVER_H

#include <ESPAsyncWebServer.h>
#include <LittleFS.h>
#include <ArduinoJson.h>
#include <Preferences.h>

void setupServer(AsyncWebServer& server, Preferences* preferences);
String getData(Preferences* preferences);
void handleData(AsyncWebServerRequest *request, uint8_t *data, size_t len, size_t index, size_t total, Preferences* preferences);

#endif
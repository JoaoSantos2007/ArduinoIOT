#ifndef SERVER_H
#define SERVER_H

#include <ESPAsyncWebServer.h>
#include <LittleFS.h>

String processor(const String& var);
void setupServer(AsyncWebServer& server);

#endif
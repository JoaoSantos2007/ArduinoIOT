#ifndef WIFI_H
#define WIFI_H

#include <WiFi.h>

void setupWiFi(const char* WIFI_SSID, const char* WIFI_PASSWORD);
bool verifWiFiStatus();
bool verifWiFi(const char* WIFI_SSID, const char* WIFI_PASSWORD);
bool reconnectWiFi(const char* WIFI_SSID, const char* WIFI_PASSWORD);

#endif
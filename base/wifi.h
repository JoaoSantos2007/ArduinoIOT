#ifndef WIFI_H
#define WIFI_H

#include <WiFi.h>
#include <Preferences.h>

void setupWiFi(Preferences& preferences);
void startAccessPoint(Preferences& preferences);
void verifyWiFiConnection(Preferences& preferences);

#endif
#ifndef MQTT_H
#define MQTT_H

#include <WiFi.h>
#include <PubSubClient.h>
#include <ArduinoJson.h>
#include <Preferences.h>

void setupMQTT(PubSubClient& client, Preferences& preferences);
void verifyMQTTConnection(PubSubClient& client, Preferences& preferences);
bool reconnectMQTT(PubSubClient& client, Preferences& preferences);
void receiveMQTT(char* topic, byte* payload, unsigned int length);
void sendMQTT(PubSubClient& client, Preferences& preferences, StaticJsonDocument<256> doc);

#endif

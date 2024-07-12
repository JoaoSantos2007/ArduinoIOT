#ifndef MQTT_H
#define MQTT_H

#include <PubSubClient.h>
#include <ArduinoJson.h>

void setupMQTT(PubSubClient& client, const char* MQTT_IP, const int MQTT_PORT);
bool verifMQTT(PubSubClient& client, const char* MQTT_ID, const char* SUBSCRIBE_TOPIC, const char* MQTT_USER, const char* MQTT_PASSWORD);
bool reconnectMQTT(PubSubClient& client, const char* MQTT_ID, const char* SUBSCRIBE_TOPIC, const char* MQTT_USER, const char* MQTT_PASSWORD);
void receiveMQTT(char* topic, byte* payload, unsigned int length);
void sendMQTT(PubSubClient& client, const char* PUBLISH_TOPIC, StaticJsonDocument<256> doc);

#endif
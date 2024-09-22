#ifndef SENSOR_H
#define SENSOR_H

#include <Arduino.h>
#include <ArduinoJson.h>
#include <DHT.h>
#include <PubSubClient.h>
#include <Preferences.h>
#include <cstring>

void setupSensors(StaticJsonDocument<2048> &sensorsDoc, Preferences &preferences);
void readSensors(StaticJsonDocument<2048> &sensorsDoc, PubSubClient &client, Preferences &preferences, void (*sendMQTT)(PubSubClient&, Preferences&, StaticJsonDocument<256>));
void sensorCallback(Preferences& preferences, const JsonDocument& doc);
void updateLightState(int light_pin, bool manual, int state);
bool readSwitch(JsonObject sensor);
void readDHT(JsonObject sensor, float &temperature, float &humidity, float &heatIndex);
void readLuminosity();

#endif
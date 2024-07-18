#ifndef SENSOR_H
#define SENSOR_H

#include <Arduino.h>
#include <ArduinoJson.h>

void setupSensors();
void updateLightState(int light_pin);
void readSensors();
void sensorCallback(const JsonDocument& doc);

#endif
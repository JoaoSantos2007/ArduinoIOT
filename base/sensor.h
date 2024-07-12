#ifndef SENSOR_H
#define SENSOR_H

#include <Arduino.h>

void setupSensors();
void updateLightState(int light_pin);
void readSensors();

#endif
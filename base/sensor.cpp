/*
======================================
          Sensor Functions
======================================
*/

#include "sensor.h"

// Light variables
const short int switch1_PIN = 22;
const short int switch2_PIN = 23;
const short int light1_PIN = 21;
const short int light2_PIN = 15;
short int switch1 = 0;
short int switch2 = 0;

// Delay time
long lastDebounceTime = 0;
long debounceDelay = 10000;

// Setup sensors
void setupSensors(){
  pinMode(switch1_PIN, INPUT);
  pinMode(switch2_PIN, INPUT);
  pinMode(light1_PIN, OUTPUT);
  pinMode(light2_PIN, OUTPUT);
}

// Update light state
void updateLightState(int light_pin){
  int newState = !digitalRead(light_pin);
  digitalWrite(light_pin, newState);
}

// Read light switches
void readSensors(){
  if(switch1 != digitalRead(switch1_PIN)){
    switch1 = !switch1;
    updateLightState(light1_PIN);
  }

  if(switch2 != digitalRead(switch2_PIN)){
    switch2 = !switch2;
    updateLightState(light2_PIN);
  }
}
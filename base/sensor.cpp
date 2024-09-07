/*
======================================
          Sensor Functions
======================================
*/

#include "sensor.h"

// Light variables
const short int switch1_PIN = 35;
const short int switch2_PIN = 25;
const short int light1_PIN = 32;
const short int light2_PIN = 33;
const short int luminosity_PIN = 34;
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
  //pinMode(luminosity_PIN, INPUT);
  //analogReadResolution(10);
}

// Update light state
void updateLightState(int light_pin){
  int newState = !digitalRead(light_pin);
  digitalWrite(light_pin, newState);
}

// Read light switches
void readSwitches(){
  if(switch1 != digitalRead(switch1_PIN)){
    switch1 = !switch1;
    updateLightState(light1_PIN);
  }

  if(switch2 != digitalRead(switch2_PIN)){
    switch2 = !switch2;
    updateLightState(light2_PIN);
  }
}

void readLuminosity(){
  float volts =  analogRead(luminosity_PIN) * 5 / 1024.0; // Convert reading to VOLTS
  float VoltPercent = analogRead(luminosity_PIN) / 1024.0 * 100; //Reading to Percent of Voltage

  //Conversions from reading to LUX
  float amps = volts / 10000.0;  // em 10,000 Ohms (Convert to Current)
  float microamps = amps * 1000000; // Convert to Microamps
  float lux = microamps * 2.0; // Convert to Lux */

  // Output Serial
  Serial.print("LUX - ");
  Serial.print(lux);
  Serial.println(" lx");
  Serial.print(VoltPercent);
  Serial.println("%");
  Serial.print(volts);
  Serial.println(" volts");
  Serial.print(amps);
  Serial.println(" amps");
  Serial.print(microamps);
  Serial.println(" microamps");
}

void readSensors(){
  //readSwitches();
  //readLuminosity();

  //delay(3000);
}

void sensorCallback(const JsonDocument& doc){
  Serial.println("Sensor callback called");
  serializeJsonPretty(doc, Serial);
  
  if(doc["test"] == "ok1") updateLightState(light1_PIN);
  if(doc["test"] == "ok2") updateLightState(light2_PIN);
}
//Import libraries
#include "sensor.h"
#include "server.h"
#include "wifi.h"
#include "mqtt.h"

WiFiClient wifiClient;
AsyncWebServer serverClient(80);
PubSubClient mqttClient(wifiClient);
Preferences preferences;

//Verif wifi and mqtt connetions
void verifyConnections(){
  verifyWiFiConnection(preferences);
  verifyMQTTConnection(mqttClient, preferences);
}

/*
======================================
           Arduino Functions
======================================
*/

void setup(){
  Serial.begin(9600);
  Serial.println("Started!");
  
  // Initialize Preferences
  preferences.begin("esp32", false);

  setupSensors();
  setupWiFi(preferences);
  setupMQTT(mqttClient, preferences, sensorCallback);
  setupServer(serverClient, &preferences);
}

void loop(){
  readSensors();
  verifyConnections();
}
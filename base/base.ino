//Import libraries
#include "conf.h" // Here are the enviroment variables
#include "sensor.h"
#include "server.h"
#include "wifi.h"
#include "mqtt.h"

WiFiClient wifiClient;
AsyncWebServer serverClient(80);
PubSubClient mqttClient(wifiClient);

//Verif wifi and mqtt connetions
void verifConnections(){
  verifWiFi(WIFI_SSID, WIFI_PASSWORD);
  verifMQTT(mqttClient, MQTT_ID, SUBSCRIBE_TOPIC, MQTT_USER, MQTT_PASSWORD);
}

/*
======================================
           Arduino Functions
======================================
*/


// Setup function
void setup(){
  Serial.begin(9600);
  Serial.println("started!");

  setupSensors();
  setupWiFi(WIFI_SSID, WIFI_PASSWORD);
  setupMQTT(mqttClient, MQTT_IP, MQTT_PORT);
  setupServer(serverClient);
  verifConnections();
}

// Loop function
void loop(){
  readSensors();
  verifConnections();
}
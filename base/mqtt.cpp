/*
=========================================
            MQTT FUNCTIONS
=========================================
*/

#include "mqtt.h"

long lastMQTTReconnectAttempt = 0;

// Setup MQTT
void setupMQTT(PubSubClient& client, const char* MQTT_IP, const int MQTT_PORT){
  client.setServer(MQTT_IP, MQTT_PORT);
  client.setCallback(receiveMQTT);
}

// Verif MQTT connection and Reconnect if needed
bool verifMQTT(PubSubClient& client, const char* MQTT_ID, const char* SUBSCRIBE_TOPIC, const char* MQTT_USER, const char* MQTT_PASSWORD){
  if (!client.connected()) {
    long now = millis();

    if (now - lastMQTTReconnectAttempt > 5000) {
      lastMQTTReconnectAttempt = now;
      
      // Attempt to reconnect
      if (reconnectMQTT(client, MQTT_ID, SUBSCRIBE_TOPIC, MQTT_USER, MQTT_PASSWORD)) {
        lastMQTTReconnectAttempt = 0;
        return true;
      } else {
        return false;
      }
    } else {
      return false;
    }
  }else{
    client.loop(); //Keep mqtt connected
    return true;
  }
}

// Reconnect MQTT connection
bool reconnectMQTT(PubSubClient& client, const char* MQTT_ID, const char* SUBSCRIBE_TOPIC, const char* MQTT_USER, const char* MQTT_PASSWORD){
  if (client.connect(MQTT_ID, MQTT_USER, MQTT_PASSWORD)){
    client.subscribe(SUBSCRIBE_TOPIC);
    Serial.println("mqtt");

    return true;
  }
  
  return false;
}

// Receive a broker message
void receiveMQTT(char* topic, byte* payload, unsigned int length){
  Serial.println("Ok111");
  String msg;
  //obtem a string do payload recebido
  for (int i = 0; i < length; i++){
    char c = (char)payload[i];
    msg += c;
  }

  Serial.print(F("Receiving: "));
  Serial.println(msg);

  StaticJsonDocument<2048> doc;
  deserializeJson(doc, payload);
}

// Send a message in MQTT
void sendMQTT(PubSubClient& client, const char* PUBLISH_TOPIC, StaticJsonDocument<256> doc){
  char out[256];
  serializeJson(doc, out);
  client.publish(PUBLISH_TOPIC, out);
}
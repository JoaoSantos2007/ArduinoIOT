/*
=========================================
            MQTT FUNCTIONS
=========================================
*/

#include "mqtt.h"

const unsigned long ReconnectBreakTime = 10 * 1000; // 10 seconds
unsigned long lastMQTTReconnectAttempt = 0;

// Setup MQTT
void setupMQTT(PubSubClient& client, Preferences& preferences){
  String mqttServer = preferences.getString("MQTT_ADDRESS", "");
  int mqttPort = preferences.getInt("MQTT_PORT", 0);

  if (mqttServer.length() > 0 && mqttPort > 0) {
    IPAddress mqttIP;
    mqttIP.fromString(mqttServer);

    client.setServer(mqttIP, mqttPort);
    client.setCallback(receiveMQTT);
  }
}

// Verif MQTT connection and Reconnect if needed
void verifyMQTTConnection(PubSubClient& client, Preferences& preferences){
  if (WiFi.status() != WL_CONNECTED) return;
  
  if(!client.connected()) {
    if (millis() - lastMQTTReconnectAttempt >= ReconnectBreakTime) {
      lastMQTTReconnectAttempt = millis();
      reconnectMQTT(client, preferences); // Attempt to reconnect
    } 
  } else {
    client.loop(); // Keep MQTT connected
  }
}

// Reconnect MQTT connection
bool reconnectMQTT(PubSubClient& client, Preferences& preferences){
  String deviceName = preferences.getString("DEVICE_NAME", "esp32");
  String mqttUser = preferences.getString("MQTT_USER", "");
  String mqttPassword = preferences.getString("MQTT_PASSWORD", "");
  String subscribeTopic = preferences.getString("MQTT_SUBSCRIBE", "");

  bool connected = client.connect(deviceName.c_str(), mqttUser.c_str(), mqttPassword.c_str());

  if (connected){
    client.subscribe(subscribeTopic.c_str());
    Serial.println("Connected to MQTT broker!");

    return true;
  }
  
  return false;
}

// Receive a broker message
void receiveMQTT(char* topic, byte* payload, unsigned int length){
  Serial.println("Message received");
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
void sendMQTT(PubSubClient& client, Preferences& preferences, StaticJsonDocument<256> doc){
  char out[256];
  serializeJson(doc, out);
  client.publish(preferences.getString("MQTT_PUBLISH", "").c_str(), out);
}

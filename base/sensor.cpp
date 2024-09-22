/*
======================================
          Sensor Functions
======================================
*/

#include "sensor.h"
DHT* dht;

// Setup sensors
void setupSensors(StaticJsonDocument<2048> &sensorsDoc, Preferences &preferences){
  String sensors = preferences.getString("SENSORS", "[]");

  DeserializationError error = deserializeJson(sensorsDoc, sensors);
  if (error) return;
  
  for (JsonObject sensor : sensorsDoc.as<JsonArray>()) {
    String type = sensor["type"];
    JsonArray pins = sensor["pins"];

    // Configura os pinos de acordo com o tipo de sensor
    if (type == "light") {
      pinMode(pins[0].as<const int>(), INPUT);
      pinMode(pins[1].as<const int>(), OUTPUT);

      sensor["switch"] = 0;
      sensor["interval"] = 0;
      sensor["lastTime"] = 0;
    } else if (type == "dht") {
      pinMode(pins[0].as<const int>(), INPUT);

      dht = new DHT(pins[0].as<const int>(), DHT11);
      dht->begin();

      sensor["interval"] = 2000;
      sensor["lastTime"] = 0;
    }
  }

  serializeJsonPretty(sensorsDoc, Serial);
}

void readSensors(StaticJsonDocument<2048> &sensorsDoc, PubSubClient &client, Preferences &preferences, void (*sendMQTT)(PubSubClient&, Preferences&, StaticJsonDocument<256>)){
  String deviceName = preferences.getString("DEVICE_NAME");

  for (JsonObject sensor : sensorsDoc.as<JsonArray>()) {
    unsigned long currentMillis = millis();
    if (currentMillis - sensor["lastTime"].as<const unsigned long>() < sensor["interval"].as<const unsigned long>()) return;

    
    sensor["lastTime"] = currentMillis;
    String type = sensor["type"];

    StaticJsonDocument<256> doc;
    doc["device"] = deviceName;
    doc["id"] = sensor["id"];
    doc["type"] = sensor["type"];

    // lê os sensores de acordo com o tipo
    if (type == "light") {
      bool changed = readSwitch(sensor);

      if(changed){
        doc["light"] = digitalRead(sensor["pins"][1].as<const int>());

        sendMQTT(client, preferences, doc);
      }
    } else if (type == "dht") {
      float temperature, humidity, heatIndex;
      readDHT(sensor, temperature, humidity, heatIndex);
      doc["temperature"] = temperature;
      doc["humidity"] = humidity;
      doc["heatIndex"] = heatIndex;

      sendMQTT(client, preferences, doc);
    }
  }
}

void sensorCallback(Preferences& preferences, const JsonDocument& doc){
  String sensors = preferences.getString("SENSORS", "[]");

  StaticJsonDocument<2048> sensorsDoc;
  DeserializationError error = deserializeJson(sensorsDoc, sensors);
  if (error) return;

  for (JsonObject sensor : sensorsDoc.as<JsonArray>()) {
    if (strcmp(doc["id"].as<const char*>(), sensor["id"].as<const char*>()) == 0){
      String type = sensor["type"];

      if (type == "light") {
        updateLightState(sensor["pins"][1].as<const int>(), true, doc["light"].as<const int>());
      }
    }
  }
}

// Update light state
void updateLightState(int light_pin, bool manual = false, int state = 0){
  int newState = !digitalRead(light_pin);
  if(manual) newState = state; 

  digitalWrite(light_pin, newState);
}

// Read light switch
bool readSwitch(JsonObject sensor){
  if(sensor["switch"] != digitalRead(sensor["pins"][0].as<const int>())){
    sensor["switch"] = !sensor["switch"].as<const int>();
    updateLightState(sensor["pins"][1].as<const int>());

    return true;
  }

  return false;
}

void readDHT(JsonObject sensor, float &temperature, float &humidity, float &heatIndex){
  humidity = dht->readHumidity();
  temperature = dht->readTemperature();

  if (isnan(humidity) || isnan(temperature)) return;

  // Compute heat index in Celsius (isFahreheit = false)
  heatIndex = dht->computeHeatIndex(temperature, humidity, false);
}

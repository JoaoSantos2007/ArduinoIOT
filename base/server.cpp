/*
=========================================
            SERVER FUNCTIONS
=========================================
*/

#include "server.h"

void setupServer(AsyncWebServer& server, Preferences* preferences){
  if(LittleFS.begin(true)){
    Serial.println("LittleFS mounted successfully");
  }else{
    Serial.println("An error has occurred while mounting LittleFS");
  }

  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(LittleFS, "/index.html", "text/html");
  });

  server.on("/index.html", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(LittleFS, "/index.html", "text/html");
  });

  server.on("/style.css", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(LittleFS, "/style.css", "text/css");
  });

  server.on("/script.js", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(LittleFS, "/script.js", "text/js");
  });

  server.on("/data", HTTP_GET, [preferences](AsyncWebServerRequest *request) {
    String jsonData = getData(preferences);
    request->send(200, "application/json", jsonData);
  });

  server.on(
    "/data", HTTP_POST, 
    [](AsyncWebServerRequest *request){}, 
    NULL, 
    [preferences](AsyncWebServerRequest *request, uint8_t *data, size_t len, size_t index, size_t total) {
      handleData(request, data, len, index, total, preferences);
    }
  );

  server.begin();
}

String getData(Preferences* preferences) {
  StaticJsonDocument<200> jsonDoc;

  JsonArray sensorOptions = jsonDoc.createNestedArray("sensorOptions");
  sensorOptions.add("light");
  sensorOptions.add("temt6000");
  sensorOptions.add("dht");
  sensorOptions.add("luminosity");

  jsonDoc["sensors"] = preferences->getString("SENSORS");
  jsonDoc["ipAddress"] = WiFi.localIP().toString();
  jsonDoc["ssid"] = preferences->getString("WIFI_SSID");
  jsonDoc["wifiPassword"] = preferences->getString("WIFI_PASSWORD");
  jsonDoc["wifiStrength"] = String(WiFi.RSSI());
  jsonDoc["mqttAddress"] = preferences->getString("MQTT_ADDRESS");
  jsonDoc["mqttPort"] = String(preferences->getInt("MQTT_PORT"));
  jsonDoc["mqttPublish"] = preferences->getString("MQTT_PUBLISH");
  jsonDoc["mqttSubscribe"] = preferences->getString("MQTT_SUBSCRIBE");
  jsonDoc["mqttUser"] = preferences->getString("MQTT_USER");
  jsonDoc["mqttPassword"] = preferences->getString("MQTT_PASSWORD");
  jsonDoc["deviceName"] = preferences->getString("DEVICE_NAME");
  jsonDoc["deviceDescription"] = preferences->getString("DESCRIPTION");
  jsonDoc["deviceChip"] = ESP.getChipModel();
  jsonDoc["freeMemory"] = String(ESP.getMinFreeHeap());
  jsonDoc["uptime"] = String(millis() / 1000);
  jsonDoc["firmware"] = "1.0.0";

  // Converter JSON para string
  String jsonString;
  serializeJson(jsonDoc, jsonString);
  return jsonString;
}

void handleData(AsyncWebServerRequest *request, uint8_t *data, size_t len, size_t index, size_t total, Preferences* preferences) {
  // Converta os dados recebidos para uma String
  String body = "";
  for (size_t i = 0; i < len; i++) {
    body += (char)data[i];
  }

  // Criação do documento JSON
  StaticJsonDocument<200> jsonDoc;
  DeserializationError error = deserializeJson(jsonDoc, body);
  
  if (error) {
    Serial.print(F("deserializeJson() failed: "));
    Serial.println(error.f_str());
    request->send(400, "application/json", "{\"status\":\"Invalid JSON\"}");
    return;
  }

  // Verificar os valores do JSON e Guardar na memória permanente
  if (jsonDoc.containsKey("sensors")) preferences->putString("SENSORS", String(jsonDoc["sensors"].as<const char*>()));
  if (jsonDoc.containsKey("ssid")) preferences->putString("WIFI_SSID", String(jsonDoc["ssid"].as<const char*>()));
  if (jsonDoc.containsKey("password")) preferences->putString("WIFI_PASSWORD", String(jsonDoc["password"].as<const char*>()));
  if (jsonDoc.containsKey("mqttIP")) preferences->putString("MQTT_ADDRESS", String(jsonDoc["mqttIP"].as<const char*>()));
  if (jsonDoc.containsKey("mqttPort")) preferences->putInt("MQTT_PORT", jsonDoc["mqttPort"].as<int>());
  if (jsonDoc.containsKey("mqttUser")) preferences->putString("MQTT_USER", String(jsonDoc["mqttUser"].as<const char*>()));
  if (jsonDoc.containsKey("mqttPassword")) preferences->putString("MQTT_PASSWORD", String(jsonDoc["mqttPassword"].as<const char*>()));
  if (jsonDoc.containsKey("mqttPub")) preferences->putString("MQTT_PUBLISH", String(jsonDoc["mqttPub"].as<const char*>()));
  if (jsonDoc.containsKey("mqttSub")) preferences->putString("MQTT_SUBSCRIBE", String(jsonDoc["mqttSub"].as<const char*>()));
  if (jsonDoc.containsKey("deviceName")) preferences->putString("DEVICE_NAME", String(jsonDoc["deviceName"].as<const char*>()));
  if (jsonDoc.containsKey("deviceDescription")) preferences->putString("DESCRIPTION", String(jsonDoc["deviceDescription"].as<const char*>()));

  // Enviar uma resposta de sucesso
  request->send(200, "application/json", "{\"success\":\"OK\"}");

  delay(2000);

  ESP.restart();
}

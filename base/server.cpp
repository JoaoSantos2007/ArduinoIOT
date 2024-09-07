/*
=========================================
            SERVER FUNCTIONS
=========================================
*/

#include "server.h"

String processor(const String& arg, Preferences* preferences){
  if (arg == "IP_ADDRESS") return WiFi.localIP().toString();
  else if (arg == "SSID") return preferences->getString("WIFI_SSID");
  else if (arg == "WIFI_PASSWORD") return preferences->getString("WIFI_PASSWORD");
  else if (arg == "WIFI_STRENGH") return String(WiFi.RSSI());
  else if (arg == "MQTT_IP") return preferences->getString("MQTT_ADDRESS");
  else if (arg == "MQTT_PORT") return String(preferences->getInt("MQTT_PORT"));
  else if (arg == "MQTT_PUB") return preferences->getString("MQTT_PUBLISH");
  else if (arg == "MQTT_SUB") return preferences->getString("MQTT_SUBSCRIBE");
  else if (arg == "MQTT_USER") return preferences->getString("MQTT_USER");
  else if (arg == "MQTT_PASSWORD") return preferences->getString("MQTT_PASSWORD");
  else if (arg == "DEVICE_NAME") return preferences->getString("DEVICE_NAME");
  else if (arg == "DEVICE_DESCRIPTION") return preferences->getString("DESCRIPTION");
  else if (arg == "DEVICE_CHIP") return ESP.getChipModel();
  else if (arg == "FREE_MEMORY") return String(ESP.getMinFreeHeap());
  else if (arg == "UPTIME") return String(millis());
  else if (arg == "FIRMWARE_VERSION") return "1.0.0";

  return "";
}

void setupServer(AsyncWebServer& server, Preferences* preferences){
  if(LittleFS.begin(true)){
    Serial.println("LittleFS mounted successfully");
  }else{
    Serial.println("An error has occurred while mounting LittleFS");
  }

  server.on("/", HTTP_GET, [preferences](AsyncWebServerRequest *request){
    request->send(LittleFS, "/info.html", "text/html", false, [preferences](const String& arg) -> String { 
      return processor(arg, preferences); 
    });
  });

  server.on("/default.css", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(LittleFS, "/default.css", "text/css");
  });

  server.on("/info.html", HTTP_GET, [preferences](AsyncWebServerRequest *request){
    request->send(LittleFS, "/info.html", "text/html", false, [preferences](const String& arg) -> String { 
      return processor(arg, preferences); 
    });
  });

  server.on("/info.css", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(LittleFS, "/info.css", "text/css");
  });

  server.on("/info.js", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(LittleFS, "/info.js", "text/js");
  });

  server.on("/sensor.html", HTTP_GET, [preferences](AsyncWebServerRequest *request){
    request->send(LittleFS, "/sensor.html", "text/html", false, [preferences](const String& arg) -> String { 
      return processor(arg, preferences); 
    });
  });

  server.on("/sensor.css", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(LittleFS, "/sensor.css", "text/css");
  });

  server.on("/sensor.js", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(LittleFS, "/sensor.js", "text/js");
  });

  server.on("/config.html", HTTP_GET, [preferences](AsyncWebServerRequest *request){
    request->send(LittleFS, "/config.html", "text/html", false, [preferences](const String& arg) -> String { 
      return processor(arg, preferences); 
    });
  });

  server.on("/config.css", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(LittleFS, "/config.css", "text/css");
  });

  server.on("/config.js", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(LittleFS, "/config.js", "text/js");
  });

  server.on(
    "/setup", HTTP_POST, 
    [](AsyncWebServerRequest *request){}, 
    NULL, 
    [preferences](AsyncWebServerRequest *request, uint8_t *data, size_t len, size_t index, size_t total) {
      handleSetup(request, data, len, index, total, preferences);
    }
  );

  server.begin();
}

void handleSetup(AsyncWebServerRequest *request, uint8_t *data, size_t len, size_t index, size_t total, Preferences* preferences) {
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

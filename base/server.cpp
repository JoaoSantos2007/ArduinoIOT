#include "ESPAsyncWebServer.h"
/*
=========================================
            SERVER FUNCTIONS
=========================================
*/

#include "server.h"

void setupServer(AsyncWebServer& server){
  if(LittleFS.begin(true)){
    Serial.println("LittleFS mounted successfully");
  }else{
    Serial.println("An error has occurred while mounting LittleFS");
  }

  server.on("/default.css", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(LittleFS, "/default.css", "text/css");
  });

  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(LittleFS, "/index.html", "text/html", false, processor);
  });

  server.on("/index.css", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(LittleFS, "/index.css", "text/css");
  });

  server.on("/conf", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(LittleFS, "/conf.html", "text/html", false, processor);
  });

  server.on("/conf.css", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(LittleFS, "/conf.css", "text/css");
  });

  server.on("/setup", HTTP_POST, [](AsyncWebServerRequest *request){
    request->send(LittleFS, "/index.html", "text/html", false, processor);
  });

  // Start server
  server.begin();
}

String processor(const String& var){
  if(var == "IP_ADDRESS"){
    return "192.168.1.3";
  }
  return "None";
}
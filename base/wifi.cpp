/*
=========================================
            WIFI FUNCTIONS
=========================================
*/

#include "wifi.h"

long lastWIFIReconnectAttempt = 0;

//Setup WIFI
void setupWiFi(const char* WIFI_SSID, const char* WIFI_PASSWORD){
  reconnectWiFi(WIFI_SSID, WIFI_PASSWORD);
}

bool verifWiFiStatus(){
  return WiFi.status() == WL_CONNECTED;
}

//Verif WIFI connection
bool verifWiFi(const char* WIFI_SSID, const char* WIFI_PASSWORD){
  if (!verifWiFiStatus()) {
    long now = millis();
    if (now - lastWIFIReconnectAttempt > 10000) {
      lastWIFIReconnectAttempt = now;
      
      // Attempt to reconnect
      if (reconnectWiFi(WIFI_SSID, WIFI_PASSWORD)) {
        lastWIFIReconnectAttempt = 0;
      }
    }

    return false;
  } else {
    return true;
  }
}


//Reconnect WIFI connection
bool reconnectWiFi(const char* WIFI_SSID, const char* WIFI_PASSWORD){
  WiFi.mode(WIFI_STA);
  WiFi.setHostname("ESP32");
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD); // Conecta na rede WI-FI
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  // Mostra o endereço IP
  Serial.println();
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());
  
  return verifWiFiStatus();
}
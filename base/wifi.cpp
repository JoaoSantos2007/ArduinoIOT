/*
=========================================
            WIFI FUNCTIONS
=========================================
*/

#include "wifi.h"

unsigned long lastConnectionAttempt = 0;
const unsigned long connectionTimeout = 3 * 60 * 1000; // 3 minutes
bool accessPointActive = false;
bool tryingToConnect = false;

void setupWiFi(Preferences& preferences) {
  String ssid = preferences.getString("WIFI_SSID", "");
  String password = preferences.getString("WIFI_PASSWORD", "");

  // Se existir o ssid e password na memória volátil tenta a conexão senão abre o access point
  if (ssid.length() > 0 && password.length() > 0) {
    Serial.println("Attempting to connect to WiFi...");
    WiFi.begin(ssid.c_str(), password.c_str());
    tryingToConnect = true;
    lastConnectionAttempt = millis();
  } else {
    Serial.println("No WiFi credentials, starting Access Point...");
    startAccessPoint(preferences);
  }
}

void startAccessPoint(Preferences& preferences) {
  String deviceName = preferences.getString("DEVICE_NAME", "esp32");
  WiFi.softAP(deviceName.c_str());
  IPAddress IP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(IP);
  accessPointActive = true;
  tryingToConnect = false;
}

void verifyWiFiConnection(Preferences& preferences) {
  if (tryingToConnect) { // Se estiver tentando se conectar no wifi espera a conexão ou se o tempo de conexão exceder abre o access point
    if (WiFi.status() == WL_CONNECTED) { // Se conectou, define as variáveis de controle com false
      Serial.println("Connected to WiFi!");
      Serial.print("IP Address: ");
      Serial.println(WiFi.localIP());
      accessPointActive = false;
      tryingToConnect = false;
    } else if (millis() - lastConnectionAttempt >= connectionTimeout) { // Senão conectou e o tempo de conexão excedeu, abre o access point
      Serial.println("Failed to connect within timeout, starting Access Point...");
      startAccessPoint(preferences);
    }
  } else if (WiFi.status() != WL_CONNECTED && !accessPointActive) { // Se a conexão se perdeu, tenta a reconexão
    Serial.println("WiFi lost connection, attempting to reconnect...");
    WiFi.reconnect();
    tryingToConnect = true;
    lastConnectionAttempt = millis();
  } else if (WiFi.status() == WL_CONNECTED && accessPointActive) { // Se a conexão foi feita e o access point ainda estiver aberto, fecha
    Serial.println("WiFi connected, stopping Access Point...");
    WiFi.softAPdisconnect(true);
    accessPointActive = false;
  }
}
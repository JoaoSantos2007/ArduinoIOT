if(ipAddress !== "%IP_ADDRESS%") document.getElementById("ipAddress").textContent += ipAddress
if(wifiSsid !== "%SSID%") document.getElementById("wifiSsid").textContent += wifiSsid
if(wifiPassword !== "%WIFI_PASSWORD%") document.getElementById("wifiPassword").textContent += wifiPassword
if(wifiStrength !== "%WIFI_STRENGH%") document.getElementById("wifiStrength").textContent += wifiStrength
if(mqttIp !== "%MQTT_IP%") document.getElementById("mqttIp").textContent += mqttIp
if(mqttPort !== "%MQTT_PORT%") document.getElementById("mqttIp").textContent += `:${mqttPort}`
if(mqttPub !== "%MQTT_PUB%") document.getElementById("mqttPub").textContent += mqttPub
if(mqttSub !== "%MQTT_SUB%") document.getElementById("mqttSub").textContent += mqttSub
if(mqttUser !== "%MQTT_USER%") document.getElementById("mqttUser").textContent += mqttUser
if(mqttPassword !== "%MQTT_PASSWORD%") document.getElementById("mqttPassword").textContent += mqttPassword
if(deviceName !== "%DEVICE_NAME%") document.getElementById("deviceName").textContent += deviceName
if(deviceDescription !== "%DEVICE_DESCRIPTION%") document.getElementById("deviceDescription").textContent += deviceDescription
if(deviceChip !== "%DEVICE_CHIP%") document.getElementById("deviceChip").textContent += deviceChip
if(freeMemory !== "%FREE_MEMORY%") document.getElementById("freeMemory").textContent += `${Math.ceil(Number(freeMemory)/1024)}kb` 
if(uptime !== "%UPTIME%") document.getElementById("uptime").textContent += `${Math.floor(Number(uptime)/1000)} seconds` 
if(firmware !== "%FIRMWARE_VERSION%") document.getElementById("firmware").textContent += firmware

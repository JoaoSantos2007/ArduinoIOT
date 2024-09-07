const btn = document.getElementById('button');
btn.addEventListener('click', () => {
  const ssid = document.getElementById('wifi_SSID').value
  const password = document.getElementById('wifi_PASSWORD').value
  const mqttIP = document.getElementById('mqtt_IP').value
  const mqttPort = document.getElementById('mqtt_PORT').value
  const mqttUser = document.getElementById('mqtt_USER').value
  const mqttPassword = document.getElementById('mqtt_PASSWORD').value
  const mqttPub = document.getElementById('mqtt_PUBLISH').value
  const mqttSub = document.getElementById('mqtt_SUBSCRIBE').value
  const deviceName = document.getElementById('esp_NAME').value
  const deviceDescription = document.getElementById('esp_DESCRIPTION').value

  const body = {
    ssid,
    password,
    mqttIP,
    mqttPort,
    mqttUser,
    mqttPassword,
    mqttPub,
    mqttSub,
    deviceName,
    deviceDescription
  }

  const myHeaders = new Headers();
  myHeaders.append("Content-Type", "application/json");

  fetch('/setup', {
    headers: myHeaders,
    method: "POST",
    body: JSON.stringify(body) 
  })
    .then((response) => {
      response.json()
        .then((result) => {
          console.log(result)
          window.alert("Rebooting...")
        })
        .catch((err) => {
          console.error(err)
        })
    })
    .catch((err) => {
      console.error(err);
    })
});

if(wifiSsid !== "%SSID%") document.getElementById("wifi_SSID").value += wifiSsid
if(wifiPassword !== "%WIFI_PASSWORD%") document.getElementById("wifi_PASSWORD").value += wifiPassword
if(mqttIp !== "%MQTT_IP%") document.getElementById("mqtt_IP").value += mqttIp
if(mqttPort !== "%MQTT_PORT%") document.getElementById("mqtt_PORT").value += mqttPort
if(mqttPub !== "%MQTT_PUB%") document.getElementById("mqtt_PUBLISH").value += mqttPub
if(mqttSub !== "%MQTT_SUB%") document.getElementById("mqtt_SUBSCRIBE").value += mqttSub
if(mqttUser !== "%MQTT_USER%") document.getElementById("mqtt_USER").value += mqttUser
if(mqttPassword !== "%MQTT_PASSWORD%") document.getElementById("mqtt_PASSWORD").value += mqttPassword
if(deviceName !== "%DEVICE_NAME%") document.getElementById("device_NAME").value += deviceName
if(deviceDescription !== "%DEVICE_DESCRIPTION%") document.getElementById("device_DESCRIPTION").value += deviceDescription
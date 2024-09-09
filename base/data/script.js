window.addEventListener('resize', checkHeight);
window.addEventListener('DOMContentLoaded', () => {
  checkHeight()
  renderData()
  renderSensors(sensors)
});
const options = ['light', 'temt6000', 'humidity', 'temperature', 'luminosity']
//renderSensors(sensors)

document.getElementById('sensorBTN-NEW').addEventListener('click', () => {
  createSensor();
  checkHeight();
})

async function renderData(){
  try {
    const response = await fetch('/data')
    const result = await response.json()

    renderHtml(result)
  } catch (err) {
    console.error(err);
  }
}

function renderHtml(data){
  document.getElementById("ipAddress").textContent += data.ipAddress
  document.getElementById("wifiSsid").textContent += data.ssid
  document.getElementById("wifiPassword").textContent += data.wifiPassword
  document.getElementById("wifiStrength").textContent += data.wifiStrength
  document.getElementById("mqttIp").textContent += data.mqttAddress
  document.getElementById("mqttIp").textContent += `:${data.mqttPort}`
  document.getElementById("mqttPub").textContent += data.mqttPublish
  document.getElementById("mqttSub").textContent += data.mqttSubscribe
  document.getElementById("mqttUser").textContent += data.mqttUser
  document.getElementById("mqttPassword").textContent += data.mqttPassword
  document.getElementById("deviceName").textContent += data.deviceName
  document.getElementById("deviceDescription").textContent += data.deviceDescription
  document.getElementById("deviceChip").textContent += data.deviceChip
  document.getElementById("freeMemory").textContent += `${Math.ceil(Number(data.freeMemory)/1024)}kb` 
  document.getElementById("uptime").textContent += `${data.uptime} seconds` 
  document.getElementById("firmware").textContent += data.firmware

  document.getElementById("input-wifiSsid").value = data.ssid
  document.getElementById("input-wifiPassword").value = data.wifiPassword
  document.getElementById("input-mqttIp").value = data.mqttAddress
  document.getElementById("input-mqttPort").value = data.mqttPort
  document.getElementById("input-mqttPub").value = data.mqttPublish
  document.getElementById("input-mqttSub").value = data.mqttSubscribe
  document.getElementById("input-mqttUser").value = data.mqttUser
  document.getElementById("input-mqttPassword").value = data.mqttPassword
  document.getElementById("input-deviceName").value = data.deviceName
  document.getElementById("input-deviceDescription").value = data.deviceDescription
}

function showSection(sectionId) {
  // Normalizar todos os links
  const links = document.querySelectorAll('.navbar__link');
  links.forEach(link => link.classList.remove('navbar__selected'));

  // Destacar o link selecionado
  const linkToShow = document.getElementById(`navbar-${sectionId}`);
  linkToShow.classList.add('navbar__selected');

  // Esconder todas as seções
  const sections = document.querySelectorAll('.content');
  sections.forEach(section => section.classList.remove('content__active'));

  // Mostrar a seção selecionada
  const sectionToShow = document.getElementById(`content-${sectionId}`);
  sectionToShow.classList.add('content__active');

  checkHeight()
}

const configBtn = document.getElementById('btn-config');
configBtn.addEventListener('click', async () => {
  try {
    const ssid = document.getElementById('input-wifiSsid').value
    const password = document.getElementById('input-wifiPassword').value
    const mqttIP = document.getElementById('input-mqttIp').value
    const mqttPort = document.getElementById('input-mqttPort').value
    const mqttUser = document.getElementById('input-mqttUser').value
    const mqttPassword = document.getElementById('mqtt_PASSWORD').value
    const mqttPub = document.getElementById('input-mqttPub').value
    const mqttSub = document.getElementById('input-mqttSub').value
    const deviceName = document.getElementById('input-deviceName').value
    const deviceDescription = document.getElementById('input-deviceDescription').value
  
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
  
    const response = await fetch('/setup', {
      headers: myHeaders,
      method: "POST",
      body: JSON.stringify(body) 
    })

    const result = await response.json()
    console.log(result)
    window.alert("Rebooting...")
  } catch (err) {
    console.error(err);
  }
});


function checkHeight() {
  const mainElement = document.querySelector('.main');
  const navbarLinkFirstElement = document.querySelector('.navbar__link:first-child')
  const navbarLinkLastElement = document.querySelector('.navbar__link:last-child')
  const navbarElement = document.querySelector('.navbar')
  const viewportHeight = window.innerHeight;
  
  if (mainElement.scrollHeight >= viewportHeight) {
    mainElement.style.borderRadius = '0';
    navbarElement.style.borderRadius = '0';
    navbarLinkFirstElement.style.borderRadius = '0';
    navbarLinkLastElement.style.borderRadius = '0'
  } else {
    mainElement.style.borderRadius = '36px';
    navbarElement.style.borderRadius = '36px';
    navbarLinkFirstElement.style["border-top-left-radius"] = '36px';
    navbarLinkLastElement.style["border-top-right-radius"] = '36px'
  }
}

const sensors = [
  {
    id: "jksdhabfiiuehfouewf",
    type: "temperature",
    pins: [1,2,3]
  },
  {
    id: "aknfgbnojahsdfogho",
    type: "light",
    pins: [23,34]
  }
]

function renderSensors(sensors){
  sensors.forEach((sensor) => {
    const sensorElement = createSensorElement(sensor);
    
    const sensorsElement = document.getElementById('sensors')
    sensorsElement.appendChild(sensorElement)
  })
}

function renderSelectOptions(){
  const selectType = document.getElementById('sensorType-NEW')

  options.forEach(option => {
    const optionElement = document.createElement('option')
    optionElement.value = option
    optionElement.textContent = option[0].toUpperCase() + option.substring(1)
    
    selectType.appendChild(optionElement)
  })
}

function randomID(length = 15) {
  let result = '';
  const characters = 'ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789';
  const charactersLength = characters.length;
  for (let i = 0; i < length; i++) {
    result += characters.charAt(Math.floor(Math.random()
 * charactersLength));
  }

  return result;
}

/*
=========================
    Sensor Functions
=========================
*/

function createSensorConfElement(){
  const sensorConfElement = document.createElement('div')
  sensorConfElement.className = 'sensor__conf'
  
  return sensorConfElement
}

function createSensorFieldElement(content){
  const sensorFieldElement = document.createElement('p')
  sensorFieldElement.className = 'sensor__field'
  sensorFieldElement.textContent = content
  
  return sensorFieldElement
}

function createSensorIdElement(id){
  const sensorConfElement = createSensorConfElement();
  const sensorFieldElement = createSensorFieldElement('Id');
  const idElement = document.createElement('p')
  idElement.textContent = id
  
  sensorConfElement.appendChild(sensorFieldElement)
  sensorConfElement.appendChild(idElement)
  
  return sensorConfElement
}

function createSensorTypeElement(type){
  const sensorConfElement = createSensorConfElement();
  const sensorFieldElement = createSensorFieldElement('Type');
  const selectElement = document.createElement('select')
  
  options.forEach(option => {
    const optionElement = document.createElement('option')
    optionElement.value = option
    optionElement.textContent = option[0].toUpperCase() + option.substring(1)
    if(type === option) optionElement.selected = true
    
    selectElement.appendChild(optionElement)
  })
  
  sensorConfElement.appendChild(sensorFieldElement)
  sensorConfElement.appendChild(selectElement)
  
  return sensorConfElement
}

function createSensorPinElement(num, pins){
  const sensorConfElement = createSensorConfElement();
  const sensorFieldElement = createSensorFieldElement(`Pin ${num}`);
  const inputElement = document.createElement('input')
  inputElement.type = 'number'
  inputElement.value = pins[num - 1]
  
  sensorConfElement.appendChild(sensorFieldElement)
  sensorConfElement.appendChild(inputElement)
  
  return sensorConfElement
}

function createSensorDeleteElement(id){
  const sensorConfElement = createSensorConfElement();
  const sensorFieldElement = createSensorFieldElement('Del');
  sensorFieldElement.classList.add('field__del')
  const buttonElement = document.createElement('button')
  buttonElement.classList.add('sensor__btn', 'sensor__del')
  buttonElement.textContent = 'X'
  buttonElement.onclick = () => removeSensor(id)
  
  sensorConfElement.appendChild(sensorFieldElement)
  sensorConfElement.appendChild(buttonElement)
  
  return sensorConfElement
}

function createSensorElement(sensor){
  const sensorElement = document.createElement('div')
  sensorElement.id = sensor.id
  sensorElement.className = 'sensor'

  const sensorIdElement = createSensorIdElement(sensor.id);
  const sensorTypeElement = createSensorTypeElement(sensor.type);
  const sensorPin1Element = createSensorPinElement(1, sensor.pins);
  const sensorPin2Element = createSensorPinElement(2, sensor.pins);
  const sensorPin3Element = createSensorPinElement(3, sensor.pins);
  const sensorDeleteElement = createSensorDeleteElement(sensor.id);

  sensorElement.appendChild(sensorIdElement)
  sensorElement.appendChild(sensorTypeElement)
  sensorElement.appendChild(sensorPin1Element)
  sensorElement.appendChild(sensorPin2Element)
  sensorElement.appendChild(sensorPin3Element)
  sensorElement.appendChild(sensorDeleteElement)

  return sensorElement
}

function createSensor(){
  const sensorsElement = document.getElementById('sensors')

  const sensorTypeElement = document.getElementById('sensorType-NEW')
  const sensorPIN1Element = document.getElementById('sensorPIN1-NEW')
  const sensorPIN2Element = document.getElementById('sensorPIN2-NEW')
  const sensorPIN3Element = document.getElementById('sensorPIN3-NEW')
  
  const sensor = {
    "id": randomID(),
    "type": sensorTypeElement.value,
    "pins": [
      sensorPIN1Element.value,
      sensorPIN2Element.value,
      sensorPIN3Element.value,
    ]
  }

  sensorTypeElement.value = 'light';
  sensorPIN1Element.value = '';
  sensorPIN2Element.value = '';
  sensorPIN3Element.value = '';

  const sensorElement = createSensorElement(sensor)
  sensorsElement.appendChild(sensorElement)
}

function removeSensor(id){
  document.getElementById(id).remove();
  checkHeight();
}
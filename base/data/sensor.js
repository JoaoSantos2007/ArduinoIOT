const options = ['light', 'temt6000', 'humidity', 'temperature', 'luminosity']

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

function createSensorElement(sensor){
  const sensorElement = document.createElement('div')
  sensorElement.className = 'sensor'

  const sensorIdElement = createSensorIdElement(sensor.id);
  const sensorTypeElement = createSensorTypeElement(sensor.type);
  const sensorPin1Element = createSensorPinElement(1, sensor.pins);
  const sensorPin2Element = createSensorPinElement(2, sensor.pins);
  const sensorPin3Element = createSensorPinElement(3, sensor.pins);

  sensorElement.appendChild(sensorIdElement)
  sensorElement.appendChild(sensorTypeElement)
  sensorElement.appendChild(sensorPin1Element)
  sensorElement.appendChild(sensorPin2Element)
  sensorElement.appendChild(sensorPin3Element)

  return sensorElement
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

renderSelectOptions()
renderSensors(sensors)

document.getElementById('sensorBTN-NEW').addEventListener('click', () => {
  createSensor();
})
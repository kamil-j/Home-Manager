#include "SmartHome.h"

#define BUTTON_1_PIN A1
#define RELAY_1_PIN 5
#define PIR_SENSOR_1_PIN A2
#define DHT_PIN 2

const int SMART_LIGHTS_COUNT = 1;
SmartLight smartLights[] = {
  SmartLight(RELAY_1_PIN, BUTTON_1_PIN, PIR_SENSOR_1_PIN, true)
};

const int SMART_DHT_COUNT = 1;
SmartDHT smartDHTs[] = {
  SmartDHT(DHT_PIN)
};

SmartHome smartHome(smartLights, SMART_LIGHTS_COUNT, smartDHTs, SMART_DHT_COUNT);

void setup() {
}

void loop() { 
  smartHome.beSmart();
}

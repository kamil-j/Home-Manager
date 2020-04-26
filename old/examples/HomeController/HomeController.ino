#include "Home.h"

//=====================
//MY SENSORS CONFIG
#define MY_GATEWAY_SERIAL
#define MY_REPEATER_FEATURE
#define MY_NODE_ID 1
#if F_CPU == 8000000L
#define MY_BAUD_RATE 38400
#endif
#include <SPI.h>
#include <MySensors.h>
//=====================

#define LIGHT_PIN 5

const int LIGHTS_QUANTITY = 1;
Light lights[] = {
  Light(1, LIGHT_PIN)
};

Home home(lights, LIGHTS_QUANTITY);

void setup() {
}

void loop() { 
    home.control();
}

void presentation() {
	sendSketchInfo("Home", "1.0");
	home.presentation();
}

void receive(const MyMessage &message) {
    home.handleMessage(message.sensor, message.getInt());
}
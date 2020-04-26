#include "Home.h"
#include "Arduino.h"

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

//=========LIGHT==========
#define RELAY_ON LOW
#define RELAY_OFF HIGH
#define STATE_ON 1
#define STATE_OFF 0

Light::Light(int id, int pin) {
    _id = id;
    _pin = pin;
    pinMode(_pin, OUTPUT);
    digitalWrite(_pin, RELAY_OFF);
}

int Light::getId() {
	return _id;
}

void Light::presentation() {
	present(_id, S_LIGHT);
}

void Light::initialize() {
	if (loadState(_pin) == STATE_ON) {
		turnOn();
	} else {
		turnOff();
	}
}

void Light::turnOn(bool sendState) {
	digitalWrite(_pin, RELAY_ON);
	saveState(_pin, STATE_ON);
	_isOn = true;
	if (sendState) {
		sendStateToController();
	}
}

void Light::turnOff(bool sendState) {
	digitalWrite(_pin, RELAY_OFF);
	saveState(_pin, STATE_OFF);
	_isOn = false;
	if (sendState) {
		sendStateToController();
	}
}

void Light::sendStateToController() {
    MyMessage msg(_id, V_LIGHT);
	send(msg.set(_isOn ? STATE_ON : STATE_OFF));
}

//=========HOME==========

Home::Home(Light* lights, int lightsQuantity) {
    _lights = lights;
    _lightsQuantity = lightsQuantity;
}

void Home::presentation() {
    for (int i = 0; i < _lightsQuantity; ++i) {
        _lights[i].presentation();
    }
}

void Home::control() {
    if(_isNotInitialized) {
        initialize();
        _isNotInitialized = false;
    }
}

void Home::initialize() {
	for (int i = 0; i < _lightsQuantity; ++i) {
		_lights[i].initialize();
	}
}

void Home::handleMessage(int id, int newState) {
    //if (message.type == V_LIGHT) { TODO: Check message type
        handleLightMessage(id, newState);
    //}
}

void Home::handleLightMessage(int id, int newState) {
    for (int i = 0; i < _lightsQuantity; ++i) {
        if(_lights[i].getId() == id) {
            bool isOn = (bool)newState;
            if (isOn) {
                _lights[i].turnOn(false);
            } else {
                _lights[i].turnOff(false);
            }
        }
    }
}

//=========MY_SENSORS==========

extern Home home;

void presentation() {
	sendSketchInfo("Home", "1.0");
	home.presentation();
}

void receive(const MyMessage &message) {
    home.handleMessage(message.sensor, message.getInt());
}
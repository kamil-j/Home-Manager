#include "Light.h"

Light::Light(int id, int pin) {
	_id = id;
	_pin = pin;
	pinMode(_pin, OUTPUT);
    digitalWrite(_pin, RELAY_OFF);
	homeManager.registerSensor(this);
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

int Light::getId() {
	return _id;
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
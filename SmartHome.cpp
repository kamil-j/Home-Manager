#include "Arduino.h"
#include "SmartHome.h"

//=================
//MY SENSORS CONFIG
#define MY_GATEWAY_SERIAL
#define MY_REPEATER_FEATURE
#define MY_NODE_ID 1
#if F_CPU == 8000000L
#define MY_BAUD_RATE 38400
#endif
//=================

#include <SPI.h>
#include <MySensors.h>

#define BUTTON_ACTIVE LOW
#define PIR_DETECTOR_ACTIVE_TIME 20000
#define PIR_DETECTOR_GRACE_PERIOD 20000
#define RELAY_ON LOW
#define RELAY_OFF HIGH
#define STATE_ON 1
#define STATE_OFF 0

extern SmartHome smartHome;

//=========SMART_LIGHT==========

SmartLight::SmartLight(int relayPin) {
	_relayPin = relayPin;
	pinMode(_relayPin, OUTPUT);

	setInitialState();
}

SmartLight::SmartLight(int relayPin, int buttonPin) : SmartLight(relayPin) {
	_buttonPin = buttonPin;
	_debounce.attach(_buttonPin);
	_debounce.interval(5);

	pinMode(_buttonPin, INPUT_PULLUP);
}

SmartLight::SmartLight(int relayPin, int buttonPin, int pirSensorPin) : SmartLight(relayPin, buttonPin) {
	_pirSensorPin = pirSensorPin;

	pinMode(_pirSensorPin, INPUT);
	digitalWrite(_pirSensorPin, LOW);
}

void SmartLight::setInitialState() {
	if (loadState(_relayPin) == STATE_ON) {
		turnOn(false); //It is too early to send state to the controller in constructor
	} else {
		turnOff(false); //It is too early to send state to the controller in constructor
	}
}

void SmartLight::turnOn(bool sendStateToController) {
	digitalWrite(_relayPin, RELAY_ON);
	saveState(_relayPin, STATE_ON);
	_isOn = true;
	_isOnByPir = false;
	if (sendStateToController) {
		sendStateToController();
	}
}

void SmartLight::turnOff(bool sendStateToController) {
	digitalWrite(_relayPin, RELAY_OFF);
	saveState(_relayPin, STATE_OFF);
	_isOn = false;
	_isOnByPir = false;
	_pirGracePeriodStart = millis();
	if (sendStateToController) {
		sendStateToController();
	}
}

void SmartLight::changeState() {
	if (_isOn && _isOnByMotion) {
		turnOn(false); //Controller already knows that light is turned on
	} else if (_isOn) {
		turnOff();
	} else {
		turnOn();
	}
}

void SmartLight::sendStateToController() {
	MyMessage msg(childId, V_LIGHT);
	send(msg.set(_isOn ? STATE_ON : STATE_OFF));
}

bool SmartLight::isButtonActive() {
	return _debounce.update() && _debounce.read() == BUTTON_ACTIVE;
}

bool SmartLight::isPirActive() {
	if (_pirSensorPin == -1 || digitalRead(_pirSensorPin) != HIGH) {
		return false;
	}
	_pirActivatedTime = millis();
	return true;
}

void SmartLight::turnOnByPir() {
	if (!_isOn) {
		digitalWrite(_relayPin, RELAY_ON);
		_isOn = true;
		_isOnByPir = true;
		sendStateToController();
	}
}

void SmartLight::turnOffByPir() {
	if (_isOn && _isOnByPir) {
		digitalWrite(_relayPin, RELAY_OFF);
		_isOn = false;
		_isOnByPir = false;
		sendStateToController();
	}
}

bool SmartLight::shouldTurnOnByPir() {
    if (_isOnByPir) {
		return false;
	}
	unsigned long currentTime = millis();
	if (currentTime < _pirGracePeriodStart) { //Only TRUE when millis() will overflow (go back to zero), after approximately 50 days
		return currentTime > PIR_DETECTOR_GRACE_PERIOD;
	}
	return millis() - _pirGracePeriodStart > PIR_DETECTOR_GRACE_PERIOD;
}

bool SmartLight::shouldTurnOffByPir() {
	if (!_isOnByPir) {
		return false;
	}
	unsigned long currentTime = millis();
	if (currentTime < _pirActivatedTime) { //Only TRUE when millis() will overflow (go back to zero), after approximately 50 days
		return currentTime > PIR_DETECTOR_ACTIVE_TIME;
	}
	return millis() - _pirActivatedTime > PIR_DETECTOR_ACTIVE_TIME;
}

//=========SMART_HOME==========

SmartHome::SmartHome(SmartLight* smartLights, int collectionSize) {
	_smartLights = smartLights;
	_collectionSize = collectionSize;
	assignChildIds();
}

void SmartHome::assignChildIds() {
	for (int i = 0; i < _collectionSize; ++i) {
		_smartLights[i].childId = i + 1;
	}
}

void SmartHome::beSmart() {
	for (int i = 0; i < _collectionSize; ++i) {
		if (shouldReportState) {
			_smartLights[i].sendStateToController();
			shouldReportState = false;
		}
		if (_smartLights[i].isButtonActive()) {
			_smartLights[i].changeState();
		}
		if (_smartLights[i].isPirActive() && _smartLights[i].shouldTurnOnByPir()) {
			_smartLights[i].turnOnByPir();
		} else if (_smartLights[i].shouldTurnOffByPir()) {
			_smartLights[i].turnOffByPir();
		}
	}
}

void SmartHome::doPresentation() {
	for (int i = 0; i < _collectionSize; ++i) {
		present(i + 1, S_LIGHT);
	}
}

void SmartHome::handleMessage(int smartLightIndex, int newState) {
	bool isOn = (bool)newState;
	if (isOn) {
		_smartLights[smartLightIndex].turnOn(false);
	} else {
		_smartLights[smartLightIndex].turnOff(false);
	}
}

//=========MY_SENSORS==========

void presentation() {
	sendSketchInfo("SmartHome", "1.0");
	smartHome.doPresentation();
}

void receive(const MyMessage &message) {
	if (message.type == V_LIGHT) {
		smartHome.handleMessage(message.sensor - 1, message.getInt());
	}
}

#include "Home.h"
#include "MySensorsDefinitions.h"

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
#include "HomeManager.h"

void HomeManager::before() {
}

void HomeManager::presentation() {
    sendSketchInfo(SKETCH_NAME, SKETCH_VERSION);
    for (List<Light*>::iterator itr = lights.begin(); itr != lights.end(); ++itr) {
        Light* light = *itr;
        light->presentation();
    }
    for (List<SensorDHT*>::iterator itr = sensors.begin(); itr != sensors.end(); ++itr) {
        SensorDHT* sensor = *itr;
        sensor->presentation();
    }
}

void HomeManager::setup() {

}

void HomeManager::loop() {
    if(_isNotInitialized) {
        initialize();
        _isNotInitialized = false;
    }
    for (List<SensorDHT*>::iterator itr = sensors.begin(); itr != sensors.end(); ++itr) {
        SensorDHT* sensor = *itr;
        sensor->onLoop();
    }
}

void HomeManager::receive(const MyMessage & msg) {
    if (msg.type == V_LIGHT) {
        receiveLightMessage(msg);
    }
}

void HomeManager::receiveLightMessage(const MyMessage & msg) {
    int lightId = msg.sensor;
    bool isOn = msg.getBool();

    for (List<Light*>::iterator itr = lights.begin(); itr != lights.end(); ++itr) {
        Light* light = *itr;
        if(light->getId() == lightId) {
            if (isOn) {
                light->turnOn(false);
            } else {
                light->turnOff(false);
            }
            return;
        }
    }
}

void HomeManager::registerSensor(Light* light) {
	lights.push(light);
}

void HomeManager::registerSensor(SensorDHT* sensor) {
	sensors.push(sensor);
}

void HomeManager::initialize() {
    for (List<Light*>::iterator itr = lights.begin(); itr != lights.end(); ++itr) {
        Light* light = *itr;
        light->initialize();
    }
}
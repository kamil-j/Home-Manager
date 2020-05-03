#include "HomeManager.h"

void HomeManager::before() {
}

void HomeManager::presentation() {
    sendSketchInfo(SKETCH_NAME, SKETCH_VERSION);
    for (List<Sensor*>::iterator itr = sensors.begin(); itr != sensors.end(); ++itr) {
        Sensor* sensor = *itr;
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
    for (List<Sensor*>::iterator itr = sensors.begin(); itr != sensors.end(); ++itr) {
        Sensor* sensor = *itr;
        sensor->onLoop();
    }
}

void HomeManager::receive(const MyMessage & message) {
    int sensorId = message.sensor;
    for (List<Sensor*>::iterator itr = sensors.begin(); itr != sensors.end(); ++itr) {
        Sensor* sensor = *itr;
        if(sensor->getId() == sensorId) {
            sensor->onReceive((MyMessage*) &message);
            return;
        }
    }
}

void HomeManager::registerSensor(Sensor* sensor) {
	sensors.push(sensor);
}

void HomeManager::initialize() {
    for (List<Sensor*>::iterator itr = sensors.begin(); itr != sensors.end(); ++itr) {
        Sensor* sensor = *itr;
        sensor->initialize();
    }
}
#include "HomeManager.h"

void HomeManager::before() {
}

void HomeManager::presentation() {
    sendSketchInfo(SKETCH_NAME, SKETCH_VERSION);
    for (List<Entity*>::iterator itr = entities.begin(); itr != entities.end(); ++itr) {
        Entity* entity = *itr;
        entity->presentation();
    }
}

void HomeManager::setup() {
}

void HomeManager::loop() {
    if(_isNotInitialized) {
        initialize();
        _isNotInitialized = false;
    }
    for (List<Entity*>::iterator itr = entities.begin(); itr != entities.end(); ++itr) {
        Entity* entity = *itr;
        entity->onLoop();
    }
    for (List<Supervisor*>::iterator itr = supervisors.begin(); itr != supervisors.end(); ++itr) {
        Supervisor* supervisor = *itr;
        supervisor->onLoop();
    }
}

void HomeManager::receive(const MyMessage & message) {
    int entityId = message.sensor;
    for (List<Entity*>::iterator itr = entities.begin(); itr != entities.end(); ++itr) {
        Entity* entity = *itr;
        if(entity->getId() == entityId) {
            entity->onReceive((MyMessage*) &message);
            return;
        }
    }
}

void HomeManager::registerEntity(Entity* entity) {
	entities.push(entity);
}

void HomeManager::registerSupervisor(Supervisor* supervisor) {
	supervisors.push(supervisor);
}

void HomeManager::initialize() {
    for (List<Entity*>::iterator itr = entities.begin(); itr != entities.end(); ++itr) {
        Entity* entity = *itr;
        entity->initialize();
    }
}
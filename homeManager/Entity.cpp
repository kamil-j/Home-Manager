#include "Entity.h"

Entity::Entity(int pin) {
	_pin = pin;
	homeManager.registerEntity(this);
}

Entity::Entity(int id, int pin) {
	_id = id;
	_pin = pin;
	homeManager.registerEntity(this);
}

int Entity::getId() {
	return _id;
}
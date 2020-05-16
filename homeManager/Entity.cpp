#include "Entity.h"

Entity::Entity(int pin) {
	_pin = pin;
	homeManager.registerEntity(this);
}

Entity::Entity(int id, mysensors_data_t dataType, int pin) : _msg(id, dataType) {
	_id = id;
	_pin = pin;
	homeManager.registerEntity(this);
}

int Entity::getId() {
	return _id;
}
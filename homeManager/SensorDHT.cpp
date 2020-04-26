#include "SensorDHT.h"

SensorDHT::SensorDHT(int id, int pin): _dht(pin, DHT11), _msg(id, V_TEMP) {
	_id = id;
	_pin = pin;
	_dht.begin();
	homeManager.registerSensor(this);
}

void SensorDHT::presentation() {
    present(_id, S_TEMP);
}

void SensorDHT::onLoop() {
    if(millis() - _lastUpdateTime < 5000) {
        return;
    }
    _lastUpdateTime = millis();
    float temperature = _dht.readTemperature();
    send(_msg.set(temperature, 1));
}
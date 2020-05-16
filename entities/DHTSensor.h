#ifndef SensorDHT_h
#define SensorDHT_h

#include "homeManager/internalEntities/DHTHumiditySensor.h"
#include "homeManager/internalEntities/DHTTemperatureSensor.h"
#include <DHT.h>

class DHTSensor: public Supervisor {
public:
    DHTSensor(int temperatureId, int humidityId, int pin): Supervisor(), _temperatureSensor(temperatureId), _humiditySensor(humidityId), _dht(pin, DHT11) {
        _dht.begin();
    }

    void onLoop() {
        if(millis() - _lastUpdateTime > DHT_UPDATE_TIME) {
            updateTemperature();
            updateHumidity();
            _lastUpdateTime = millis();
        }
    }

private:
    DHTTemperatureSensor _temperatureSensor;
    DHTHumiditySensor _humiditySensor;
    DHT _dht;
    unsigned long _lastUpdateTime = 0;
    bool _includeHumidity = false;

    void updateTemperature() {
        float temperature = _dht.readTemperature();
        Serial.println(temperature);
        _temperatureSensor.update(temperature);
    }

    void updateHumidity() {
        float humidity = _dht.readHumidity();
        _humiditySensor.update(humidity);
    }
};

#endif
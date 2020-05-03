#ifndef SensorDHT_h
#define SensorDHT_h

#include <DHT.h>

class DHTSensor: public Sensor {
public:
    DHTSensor(int id, int pin): Sensor(id, pin), _msg(id, V_TEMP), _dht(pin, DHT11) {
        _dht.begin();
    }

    void presentation() {
        present(_id, S_TEMP);
    }

    void initialize() {}

    void onLoop() {
        if(millis() - _lastUpdateTime < 5000) {
            return;
        }
        _lastUpdateTime = millis();
        float temperature = _dht.readTemperature();
        send(_msg.set(temperature, 1));
    }

    void onReceive(MyMessage* message) {}

private:
    DHT _dht;
    MyMessage _msg;
    unsigned long _lastUpdateTime = 0;
};

#endif
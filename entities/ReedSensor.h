#ifndef ReedSensor_h
#define ReedSensor_h

#include <Bounce2.h>

class ReedSensor: public Entity {
public:
    ReedSensor(int id, int pin): Entity(id, V_TRIPPED, pin) {
        _debounce.attach(pin);
        _debounce.interval(5);

        pinMode(pin,INPUT);
        digitalWrite(pin,HIGH);
    }

    void presentation() {
        present(_id, S_DOOR);
    }

    void onLoop() {
        _debounce.update();
        int newValue = _debounce.read();

        if (newValue != _previousValue) {
            send(_msg.set(newValue == HIGH ? 1 : 0));
            _previousValue = newValue;
        }
    }

private:
    Bounce _debounce = Bounce();
    int _previousValue = -1;
};

#endif
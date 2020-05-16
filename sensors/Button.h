#ifndef Button_h
#define Button_h

#include <Bounce2.h>

class Button: public Sensor {
public:
    Button(int pin, Sensor* sensor): Sensor(pin) {
        _sensor = sensor;

        _debounce.attach(_pin);
        _debounce.interval(5);

        pinMode(_pin, INPUT_PULLUP);
    }

    void onLoop() {
        if(isActive()) {
            _sensor->onButtonEvent();
        }
    }
private:
    Sensor* _sensor;
    Bounce _debounce = Bounce();

    bool isActive() {
        return _debounce.update() && _debounce.read() == BUTTON_ACTIVE;
    }
};

#endif
#ifndef Button_h
#define Button_h

#include <Bounce2.h>

class Button: public Entity {
public:
    Button(int pin, Entity* entity): Entity(pin) {
        _entity = entity;

        _debounce.attach(_pin);
        _debounce.interval(5);

        pinMode(_pin, INPUT_PULLUP);
    }

    void onLoop() {
        if(isActive()) {
            _entity->onButtonEvent();
        }
    }
private:
    Entity* _entity;
    Bounce _debounce = Bounce();

    bool isActive() {
        return _debounce.update() && _debounce.read() == BUTTON_ACTIVE;
    }
};

#endif
#ifndef PIRSensor_h
#define PIRSensor_h

#include <Bounce2.h>

class PIRSensor: public Entity {
public:
    PIRSensor(int id, int pin, Entity* entity): Entity(id, V_ARMED, pin) {
        _entity = entity;
    }

    void presentation() {
        present(_id, S_MOTION);
    }

    void initialize() {
        if (loadState(_pin) == STATE_ON) {
            turnOn();
        } else {
            turnOff();
        }
        sendStateToController();
    }

    void onLoop() {
        if(_isOn && isActive()) {
            _lastActiveTime = millis();
            if(!_isAlreadyActivated) {
                _entity->onPirEvent(STATE_ON);
                _isAlreadyActivated = true;
            }
        } else if (_isAlreadyActivated && shouldDeactivate()) {
            _entity->onPirEvent(STATE_OFF);
            _isAlreadyActivated = false;
        }
    }

    void onReceive(MyMessage* message) {
        if (message->type == V_ARMED) {
            bool isOn = message->getBool();
            if (isOn) {
                turnOn();
            } else {
                turnOff();
            }
        }
    }
private:
    Entity* _entity;
    bool _isOn = false;
    bool _isAlreadyActivated = false;
    unsigned long _lastActiveTime = 0;

    void turnOn() {
        saveState(_pin, STATE_ON);
        _isOn = true;
    }

    void turnOff() {
        saveState(_pin, STATE_OFF);
        _isOn = false;
    }

    bool isActive() {
        return digitalRead(_pin) == HIGH;
    }

    bool shouldDeactivate() {
        unsigned long currentTime = millis();
        if (currentTime < _lastActiveTime) { //Only TRUE when millis() will overflow (go back to zero), after approximately 50 days
            return currentTime > PIR_DETECTOR_ACTIVE_TIME;
        }
        return millis() - _lastActiveTime > PIR_DETECTOR_ACTIVE_TIME;
    }

    void sendStateToController() {
        send(_msg.set(_isOn ? STATE_ON : STATE_OFF));
    }
};

#endif
#ifndef PIRSensor_h
#define PIRSensor_h

#include <Bounce2.h>

class PIRSensor: public Sensor {
public:
    PIRSensor(int id, int pin, Sensor* sensor): Sensor(id, pin), _msg(id, V_ARMED) {
        _sensor = sensor;
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
        if(!_isOn) {
            return;
        }

        if(isActive()) {
            _activated = true;
            _sensor->onPirSensorEvent(_activated);
        }
        //TODO: Do not call onPirSensorEvent every time
        _activated = false;
        _sensor->onPirSensorEvent(_activated);
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
    Sensor* _sensor;
    bool _isOn = false;
    bool _activated = false;
    MyMessage _msg;

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

    void sendStateToController() {
        send(_msg.set(_isOn ? STATE_ON : STATE_OFF));
    }
};

#endif
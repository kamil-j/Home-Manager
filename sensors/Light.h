#ifndef Light_h
#define Light_h

class Light: public Sensor {
public:
    Light(int id, int pin): Sensor(id, pin), _msg(id, V_LIGHT) {
        pinMode(_pin, OUTPUT);
        digitalWrite(_pin, RELAY_OFF);
    }

    void presentation() {
        present(_id, S_LIGHT);
    }

    void initialize() {
    	if (loadState(_pin) == STATE_ON) {
    		turnOn();
    	} else {
    		turnOff();
    	}
    }

    void onLoop() {}

    void onReceive(MyMessage* message) {
        if (message->type == V_LIGHT) {
            bool isOn = message->getBool();
            if (isOn) {
                turnOn(false);
            } else {
                turnOff(false);
            }
        }
    }

private:
    bool _isOn = false;
    MyMessage _msg;

    void turnOn(bool sendState = true) {
        digitalWrite(_pin, RELAY_ON);
        saveState(_pin, STATE_ON);
        _isOn = true;
        if (sendState) {
            sendStateToController();
        }
    }

    void turnOff(bool sendState = true) {
        digitalWrite(_pin, RELAY_OFF);
        saveState(_pin, STATE_OFF);
        _isOn = false;
        if (sendState) {
            sendStateToController();
        }
    }

    void sendStateToController() {
    	send(_msg.set(_isOn ? STATE_ON : STATE_OFF));
    }
};

#endif
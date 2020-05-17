#ifndef Light_h
#define Light_h

class Light: public Entity {
public:
    int pirDetectorGracePeriod = DEFAULT_PIR_DETECTOR_GRACE_PERIOD;

    Light(int id, int pin): Entity(id, V_LIGHT, pin) {
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

    void onButtonEvent() {
        if (_isOn && _isOnByPir) {
            turnOn(false); //Controller already knows that light is turned on
        } else if (_isOn) {
            turnOff();
        } else {
            turnOn();
        }
    }

    void onPirEvent(bool isPirOn) {
        if (isPirOn) {
            if(shouldTurnOnByPir()) {
                turnOnByPir();
            }
        } else {
            turnOffByPir();
        }
    }

private:
    bool _isOn = false;
    bool _isOnByPir = false;
    unsigned long _pirGracePeriodStartTime = 0;

    void turnOn(bool sendState = true) {
        digitalWrite(_pin, RELAY_ON);
        saveState(_pin, STATE_ON);
        _isOn = true;
        _isOnByPir = false;
        if (sendState) {
            sendStateToController();
        }
    }

    void turnOff(bool sendState = true) {
        digitalWrite(_pin, RELAY_OFF);
        saveState(_pin, STATE_OFF);
        _isOn = false;
        _isOnByPir = false;
        _pirGracePeriodStartTime = millis();
        if (sendState) {
            sendStateToController();
        }
    }

    void sendStateToController() {
    	send(_msg.set(_isOn ? STATE_ON : STATE_OFF));
    }

    bool shouldTurnOnByPir() {
        if (_isOn) {
            return false;
        }
        unsigned long currentTime = millis();
        if (currentTime < _pirGracePeriodStartTime) { //Only TRUE when millis() will overflow (go back to zero), after approximately 50 days
            return currentTime > pirDetectorGracePeriod;
        }
        return millis() - _pirGracePeriodStartTime > pirDetectorGracePeriod;
    }

    void turnOnByPir() {
    	if (!_isOn) {
    	    digitalWrite(_pin, RELAY_ON);
    		_isOn = true;
    		_isOnByPir = true;
    		sendStateToController();
    	}
    }

    void turnOffByPir() {
    	if (_isOn && _isOnByPir) {
    		digitalWrite(_pin, RELAY_OFF);
    		_isOn = false;
    		_isOnByPir = false;
    		sendStateToController();
    	}
    }
};

#endif
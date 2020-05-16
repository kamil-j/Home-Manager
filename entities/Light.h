#ifndef Light_h
#define Light_h

class Light: public Entity {
public:
    Light(int id, int pin): Entity(id, pin), _msg(id, V_LIGHT) {
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

    void onPirEvent(bool isActive) {
        if (isActive) {
            _pirLastActiveTime = millis();
            if(shouldTurnOnByPir()) {
                turnOnByPir();
            }
            return;
        }
        if (shouldTurnOffByPir()) {
            turnOffByPir();
        }
    }

private:
    bool _isOn = false;
    bool _isOnByPir = false;
    unsigned long _pirLastActiveTime = 0;
    unsigned long _pirGracePeriodStartTime = 0;
    MyMessage _msg;

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
        if (_isOnByPir) {
            return false;
        }
        unsigned long currentTime = millis();
        if (currentTime < _pirGracePeriodStartTime) { //Only TRUE when millis() will overflow (go back to zero), after approximately 50 days
            return currentTime > PIR_DETECTOR_GRACE_PERIOD;
        }
        return millis() - _pirGracePeriodStartTime > PIR_DETECTOR_GRACE_PERIOD;
    }

    bool shouldTurnOffByPir() {
    	if (!_isOnByPir) {
    		return false;
    	}
    	unsigned long currentTime = millis();
    	if (currentTime < _pirLastActiveTime) { //Only TRUE when millis() will overflow (go back to zero), after approximately 50 days
    		return currentTime > PIR_DETECTOR_ACTIVE_TIME;
    	}
    	return millis() - _pirLastActiveTime > PIR_DETECTOR_ACTIVE_TIME;
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
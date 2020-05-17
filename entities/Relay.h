#ifndef Relay_h
#define Relay_h

class Relay: public Entity {
public:
    Relay(int id, int pin): Entity(id, V_STATUS, pin) {
        pinMode(_pin, OUTPUT);
        digitalWrite(_pin, RELAY_OFF);
    }

    void presentation() {
        present(_id, S_BINARY);
    }

    void initialize() {
    	if (loadState(_pin) == STATE_ON) {
    		turnOn();
    		send(_msg.set(STATE_ON));
    	} else {
    		turnOff();
    		send(_msg.set(STATE_OFF));
    	}
    }

    void onReceive(MyMessage* message) {
        if (message->type == V_LIGHT) {
            bool isOn = message->getBool();
            if (isOn) {
                turnOn();
            } else {
                turnOff();
            }
        }
    }

private:
    void turnOn() {
        digitalWrite(_pin, RELAY_ON);
        saveState(_pin, STATE_ON);
    }

    void turnOff() {
        digitalWrite(_pin, RELAY_OFF);
        saveState(_pin, STATE_OFF);
    }
};

#endif
#ifndef DHTTemperatureSensor_h
#define DHTTemperatureSensor_h

class DHTTemperatureSensor: public Entity {
public:
    DHTTemperatureSensor(int id): Entity(id, V_TEMP) { }

    void presentation() {
        present(_id, S_TEMP);
    }

    void update(float temperature) {
        send(_msg.set(temperature, 1));
    }
};

#endif
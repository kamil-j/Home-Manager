#ifndef DHTHumiditySensor_h
#define DHTHumiditySensor_h

class DHTHumiditySensor: public Entity {
public:
    DHTHumiditySensor(int id): Entity(id, V_HUM) { }

    void presentation() {
        present(_id, S_HUM);
    }

    void update(float humidity) {
        send(_msg.set(humidity, 1));
    }
};

#endif
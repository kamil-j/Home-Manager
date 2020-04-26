#ifndef SensorDHT_h
#define SensorDHT_h

#include <DHT.h>

class SensorDHT {
public:
    SensorDHT(int id, int pin);

    void presentation();
    int getId();
    void onLoop();

private:
    int _id = -1;
    int _pin = -1;
    const DHT _dht;
    const MyMessage _msg;
    unsigned long _lastUpdateTime = 0;
};

#endif
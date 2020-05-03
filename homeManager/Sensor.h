#ifndef Sensor_h
#define Sensor_h

class Sensor {
public:
    Sensor(int id, int pin);

    int getId();

    virtual void presentation() = 0;
    virtual void initialize() = 0;
    virtual void onLoop() = 0;
    virtual void onReceive(MyMessage* message) = 0;
protected:
    int _id = -1;
    int _pin = -1;
};

#endif
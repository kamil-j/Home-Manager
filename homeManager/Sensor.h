#ifndef Sensor_h
#define Sensor_h

class Sensor {
public:
    Sensor(int pin);
    Sensor(int id, int pin);

    int getId();

    virtual void presentation() { };
    virtual void initialize() { };
    virtual void onLoop() = 0;
    virtual void onReceive(MyMessage* message) { };
    virtual void onButtonEvent() { };
    virtual void onPirSensorEvent(bool isActive) { };
protected:
    int _id = -1;
    int _pin = -1;
};

#endif
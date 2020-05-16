#ifndef Entity_h
#define Entity_h

class Entity {
public:
    Entity(int pin);
    Entity(int id, mysensors_data_t dataType, int pin);

    int getId();

    virtual void presentation() { };
    virtual void initialize() { };
    virtual void onLoop() { };
    virtual void onReceive(MyMessage* message) { };
    virtual void onButtonEvent() { };
    virtual void onPirEvent(bool isActive) { };
protected:
    int _id = -1;
    int _pin = -1;
    MyMessage _msg;
};

#endif
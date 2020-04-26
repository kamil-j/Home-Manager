#ifndef Light_h
#define Light_h

class Light {
public:
    Light(int id, int pin);

    void presentation();
    void initialize();
    int getId();

    void turnOn(bool sendState = true);
    void turnOff(bool sendState = true);
private:
    int _id = -1;
    int _pin = -1;
    bool _isOn = false;

    void sendStateToController();
};

#endif
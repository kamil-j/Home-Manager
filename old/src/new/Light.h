#ifndef LIB_LIGHT_H
#define LIB_LIGHT_H

class Light {
public:
    Light(int id, int pin);

    int getId();
    void presentation();
    void initialize();
    void turnOn(bool sendState = true);
    void turnOff(bool sendState = true);
private:
    int _id;
    int _pin;
    bool _isOn;

    void sendStateToController();
};

#endif
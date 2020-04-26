#ifndef HOME_H
#define HOME_H

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

class Home {
public:
     Home(Light* lights, int lightsQuantity);

     void presentation();
     void control();
     void handleMessage(int id, int newState);
private:
    Light* _lights;
    int _lightsQuantity = 0;
    bool _isNotInitialized = true;

    void initialize();
    void handleLightMessage(int id, int newState);
};

#endif
#ifndef LIB_HOME_H
#define LIB_HOME_H

#include "Light.h"

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
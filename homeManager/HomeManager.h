#ifndef HomeManager_h
#define HomeManager_h

#include "Sensor.h"

class HomeManager {
public:
    void before();
    void presentation();
    void setup();
    void loop();
    void receive(const MyMessage & msg);

    void registerSensor(Sensor* sensor);
private:
    List<Sensor*> sensors;
    bool _isNotInitialized = true;

    void initialize();
};

#endif
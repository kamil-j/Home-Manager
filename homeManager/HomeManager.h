#ifndef HomeManager_h
#define HomeManager_h

#include "Light.h"
#include "SensorDHT.h"

class HomeManager {
public:
    void before();
    void presentation();
    void setup();
    void loop();
    void receive(const MyMessage & msg);

    void registerSensor(Light* light);
    void registerSensor(SensorDHT* sensor);
private:
    List<Light*> lights;
    List<SensorDHT*> sensors;
    bool _isNotInitialized = true;

    void initialize();
    void receiveLightMessage(const MyMessage & msg);
};

#endif
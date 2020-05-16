#ifndef HomeManager_h
#define HomeManager_h

#include "Entity.h"

class HomeManager {
public:
    void before();
    void presentation();
    void setup();
    void loop();
    void receive(const MyMessage & msg);

    void registerEntity(Entity* entity);
private:
    List<Entity*> entities;
    bool _isNotInitialized = true;

    void initialize();
};

#endif
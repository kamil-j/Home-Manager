#ifndef HomeManager_h
#define HomeManager_h

#include "Entity.h"
#include "Supervisor.h"

class HomeManager {
public:
    void before();
    void presentation();
    void setup();
    void loop();
    void receive(const MyMessage & msg);

    void registerEntity(Entity* entity);
    void registerSupervisor(Supervisor* supervisor);
private:
    List<Entity*> entities;
    List<Supervisor*> supervisors;
    bool _isNotInitialized = true;

    void initialize();
};

#endif
#define SKETCH_NAME "HomeManager"
#define SKETCH_VERSION "1.0"
#define MY_NODE_ID 1
#define MY_GATEWAY_SERIAL

#include <MySensors_HomeManager.h>
#include <entities/Light.h>
#include <entities/DHTSensor.h>
#include <entities/Button.h>
#include <entities/PIRSensor.h>

Light light(1, 5);
Button button(A2, &light);
PIRSensor pirSensor(2, 4, &light);

DHTSensor dhtSensor(3, 2);

void before() {
    homeManager.before();
}

void presentation() {
    homeManager.presentation();
}

void setup() {
    homeManager.setup();
}

void loop() {
    homeManager.loop();
}

void receive(const MyMessage &message) {
    homeManager.receive(message);
}

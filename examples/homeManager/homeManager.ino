#define SKETCH_NAME "HomeManager"
#define SKETCH_VERSION "1.0"
#define MY_NODE_ID 1
#define MY_GATEWAY_SERIAL

#include <MySensors_HomeManager.h>
#include <sensors/Light.h>
#include <sensors/DHTSensor.h>
#include <sensors/Button.h>

Light light(1, 5);
Button button(A2, &light);

DHTSensor dhtSensor(2, 2);

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

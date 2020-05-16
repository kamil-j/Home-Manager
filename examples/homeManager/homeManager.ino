// General settings for MySensors lib
#define SKETCH_NAME "HomeManager"
#define SKETCH_VERSION "1.0"
#define MY_NODE_ID 1
#define MY_GATEWAY_SERIAL

// Add include to HomeManager library:
#include <MySensors_HomeManager.h>

// Add includes to entities that you want to use:
#include <entities/Light.h>
#include <entities/DHTSensor.h>
#include <entities/Button.h>
#include <entities/PIRSensor.h>

// Add a light entity (relay) with homeAssistantId=1 and attached to pin 5.
Light light(1, 5);
// Add a button entity (wall switch) attached to pin A2. The button will control light entity.
Button button(A2, &light);
// Add a PIR sensor entity with homeAssistantId=2 and attached to pin 4. The PIR sensor will control light entity.
PIRSensor pirSensor(2, 4, &light);
// Add a DHT sensor entity with homeAssistantId=3 (temperature), homeAssistantId=4 (humidity) and attached to pin 2.
DHTSensor dhtSensor(3, 4, 2);

// Main Sketch - below code should be always the same (you don't have to touch it)

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

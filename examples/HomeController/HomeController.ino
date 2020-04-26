#include "Home.h"

#define LIGHT_PIN 5

const int LIGHTS_QUANTITY = 1;
Light lights[] = {
  Light(1, LIGHT_PIN)
};

Home home(lights, LIGHTS_QUANTITY);

void setup() {
}

void loop() { 
    home.control();
}
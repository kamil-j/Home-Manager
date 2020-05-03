#ifndef MySensors_HomeManager_h
#define MySensors_HomeManager_h

#include <Arduino.h>
#include "homeManager/Constants.h"

/*********Include required third-party libraries*********/
#include <MySensors.h>

/*********Include HomeManager core code*********/
#include "homeManager/List.h"
#include "homeManager/HomeManager.cpp"

extern HomeManager homeManager;
HomeManager homeManager;

#include "homeManager/Sensor.cpp"

#endif

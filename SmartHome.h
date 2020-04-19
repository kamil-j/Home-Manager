#ifndef SMART_HOME_H
#define SMART_HOME_H

#include "Arduino.h"
#include <Bounce2.h>

class SmartLight {
public:
  int childId = -1;

  SmartLight(int relayPin);
  SmartLight(int relayPin, int buttonPin);
  SmartLight(int relayPin, int buttonPin, int pirSensorPin);

  void turnOn(bool sendStateToController = true);
  void turnOff(bool sendStateToController = true);
  void turnOnByPir();
  void turnOffByPir();
  void changeState();
  void sendStateToController();
  bool isButtonActive();
  bool isPirActive();
  bool shouldTurnOffByPir();
private:
  int _relayPin = -1;
  int _buttonPin = -1;
  int _pirSensorPin = -1;
  int _pirSwitchPin = -1;
  unsigned long _pirActivatedTime = 0;
  bool _isOn = false;
  bool _isOnByPir = false;
  Bounce _debounce = Bounce();

  void setInitialState();
};

class SmartHome {
public:
  SmartHome(SmartLight* smartLights, int collectionSize);
  void beSmart();
  void doPresentation();
  void handleMessage(int smartLightIndex, int newState);
private:
  SmartLight* _smartLights;
  int _collectionSize = 0;
  bool shouldReportState = true;

  void setInitialState();
  void assignChildIds();
};

#endif

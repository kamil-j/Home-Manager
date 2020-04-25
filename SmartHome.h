#ifndef SMART_HOME_H
#define SMART_HOME_H

#include "Arduino.h"
#include <Bounce2.h>

class SmartLight {
public:
  int lightId = -1;
  int pirSwitchId = -1;

  SmartLight(int relayPin);
  SmartLight(int relayPin, int buttonPin);
  SmartLight(int relayPin, int buttonPin, int pirSensorPin);
  SmartLight(int relayPin, int buttonPin, int pirSensorPin, bool pirSwitch);

  void initialize();

  void turnLightOn(bool sendStateToController = true);
  void turnLightOff(bool sendStateToController = true);
  void turnPirSwitchOn();
  void turnPirSwitchOff();
  void turnLightOnByPir();
  void turnLightOffByPir();

  void changeLightState();

  bool isButtonActive();
  bool isPirActive();
  bool hasPirSwitch();

  bool shouldTurnLightOnByPir();
  bool shouldTurnLightOffByPir();
private:
  int _relayPin = -1;
  int _buttonPin = -1;
  int _pirSensorPin = -1;
  bool _pirSwitch = false;
  unsigned long _pirActivatedTime = 0;
  unsigned long _pirGracePeriodStart = 0;
  bool _isLightOn = false;
  bool _isLightOnByPir = false;
  bool _isPirSwitchOn = false;
  Bounce _debounce = Bounce();

  void setLightInitialState();
  void setPirSwitchInitialState();
  void sendLightStateToController();
  void sendPirSwitchStateToController();
};

class SmartHome {
public:
  SmartHome(SmartLight* smartLights, int collectionSize);
  void beSmart();
  void doPresentation();
  void handleLightMessage(int lightId, int newState);
  void handlePirSwitchMessage(int pirSwitchId, int newState);
private:
  SmartLight* _smartLights;
  int _collectionSize = 0;
  bool _isNotInitialized = true;

  void initialize();
  void assignIds();
};

#endif

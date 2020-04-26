#ifndef MY_SENSORS_DEFINITIONS_H
#define MY_SENSORS_DEFINITIONS_H

#include <stdint.h>

typedef enum {
	S_LIGHT					= 3,
} mysensors_sensor_t;

typedef enum {
	V_LIGHT					= 2,
} mysensors_data_t;

class MyMessage
{
private:
public:
	MyMessage(const uint8_t sensorId, const mysensors_data_t dataType);

	int16_t getInt(void) const;
	uint8_t getSensor(void) const;

	MyMessage& set(const char* value);
	MyMessage& set(const float value, const uint8_t decimals);
	MyMessage& set(const bool value);
	MyMessage& set(const uint8_t value);
	MyMessage& set(const uint32_t value);
	MyMessage& set(const int32_t value);
	MyMessage& set(const uint16_t value);
	MyMessage& set(const int16_t value);
};

void saveState(const uint8_t pos, const uint8_t value);
uint8_t loadState(const uint8_t pos);
bool send(MyMessage &msg, const bool requestEcho = false);
void receive(const MyMessage&) __attribute__((weak));
bool present(const uint8_t sensorId, const mysensors_sensor_t sensorType, const char *description = "", const bool requestEcho = false);

#endif
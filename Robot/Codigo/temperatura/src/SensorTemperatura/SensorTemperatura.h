#ifndef _SENSOR_TEMPERATURA_H_
#define _SENSOR_TEMPERATURA_H_

#include <Arduino.h>

#define VREF 1.10 // volts (típicamente 1.05–1.15)
#define PIN_SENSOR_TEMPERATURA A15

void sensorTemperatura_init(void);
float sensorTemperatura_read(void);
float lm35_read(void);
float tmp36_read(void);

#endif
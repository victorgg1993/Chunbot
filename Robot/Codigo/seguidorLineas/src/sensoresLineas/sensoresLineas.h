#ifndef __SENSORES_LINEAS_H_
#define __SENSORES_LINEAS_H_

#include <Arduino.h>

#define SENSOR_CENTRAL_L_PIN 41
#define SENSOR_CENTRAL_R_PIN 45
#define SENSOR_DER_PIN 42
#define SENSOR_IZQ_PIN 23

// Tiempo de debounce en ms
#define SENSORES_DEBOUNCE_MS 5

// Inicialización
void sensoresLinias_init(void);

// Polling (llamar en loop)
void sensoresLinias_polling(void);

// Lectura de sensores
bool sensorCentralL_isActive(void);
bool sensorCentralR_isActive(void);
bool sensor_der_isActive(void);
bool sensor_izq_isActive(void);

#endif
#include <Arduino.h>
#include "SensorTemperatura.h"

void sensorTemperatura_init(void)
{
    analogReference(INTERNAL1V1); // para que por USB y por batería el sensor dé el mismo valor.

    // Esta pirula es porque las primeras lecturas suelen ser un poco locas
    sensorTemperatura_read();
    delay(20);
    sensorTemperatura_read();
    delay(20);
}

float sensorTemperatura_read(void)
{
    // El robot lleva soldado un TMP36 de serie, pero acepta LM35 también.

    // Si usas LM35, activa esta línea y apaga la siguiente.
    // return lm35_read();
    return tmp36_read();
}

float lm35_read(void)
{
    int raw = analogRead(PIN_SENSOR_TEMPERATURA);
    float voltage = (raw * (VREF / 1023.0)); // volts
    return voltage * 100.0;                  // 10 mV / °C
}

float tmp36_read(void)
{
    int raw = analogRead(PIN_SENSOR_TEMPERATURA); // 0..1023
    float voltage = raw * (VREF / 1023.0);        // volts reales
    return ((voltage - 0.5) * 100.0);             // TMP36: 10 mV/°C
}
#ifndef HC_SR04_H
#define HC_SR04_H

#include <Arduino.h>

#define HCSR04_PIN_TRIGGER 3
#define HCSR04_PIN_ECHO 2

void HCSR04_init(void);
bool HCSR04_isNew();
float HCSR04_read();

// ISR (debe ser pública para attachInterrupt)
void HCSR04_echoISR();

#endif

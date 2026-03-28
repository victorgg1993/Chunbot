#include "HC-SR04.h"

static volatile unsigned long startTime = 0;
static volatile unsigned long echoDuration = 0;
static volatile bool newMeasurement = false;

void HCSR04_init(void)
{
    attachInterrupt(digitalPinToInterrupt(HCSR04_PIN_ECHO), HCSR04_echoISR, CHANGE);
    pinMode(HCSR04_PIN_TRIGGER, OUTPUT);
    pinMode(HCSR04_PIN_ECHO, INPUT);
}

bool HCSR04_isNew()
{
    // Generar pulso trigger para poderlo escuchar
    digitalWrite(HCSR04_PIN_TRIGGER, LOW);
    delayMicroseconds(2);
    digitalWrite(HCSR04_PIN_TRIGGER, HIGH);
    delayMicroseconds(10);
    digitalWrite(HCSR04_PIN_TRIGGER, LOW);

    return newMeasurement;
}

// devuelve la distancia en cm
float HCSR04_read()
{
    newMeasurement = false; // limpiar marca
    return (echoDuration * 0.0343f) / 2.0f;
}

//  interrupciones ( entra cuando llega el sonido )
void HCSR04_echoISR()
{
    int state = digitalRead(HCSR04_PIN_ECHO);

    if (state == HIGH)
    {
        startTime = micros();
    }
    else
    {
        echoDuration = micros() - startTime;
        newMeasurement = true;
    }
}
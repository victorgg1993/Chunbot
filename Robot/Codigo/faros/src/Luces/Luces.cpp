#include <Arduino.h>
#include "Luces.h"

void luces_init(void)
{
    pinMode(PIN_LUCES, OUTPUT);
    luces_write(LOW);
}

void luces_write(uint8_t status)
{
    digitalWrite(PIN_LUCES, status);
}

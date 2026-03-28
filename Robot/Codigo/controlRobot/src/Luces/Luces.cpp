#include <Arduino.h>
#include "../globals.h"
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

void luces_polling(void)
{
    if (cambio_switch_izquierdo)
    {
        cambio_switch_izquierdo = false;
        luces_write(estado_switch_izquierdo);
    }
}
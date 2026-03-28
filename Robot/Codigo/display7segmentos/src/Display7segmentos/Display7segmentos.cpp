#include <Arduino.h>
#include "Display7segmentos.h"

void display7segmentos_init(void)
{
    pinMode(DISPLAY_7SEG_A, OUTPUT);
    pinMode(DISPLAY_7SEG_B, OUTPUT);
    pinMode(DISPLAY_7SEG_C, OUTPUT);
    pinMode(DISPLAY_7SEG_D, OUTPUT);
    pinMode(DISPLAY_7SEG_E, OUTPUT);
    pinMode(DISPLAY_7SEG_F, OUTPUT);
    pinMode(DISPLAY_7SEG_G, OUTPUT);

    display7segmentos_off();
}

void display7segmentos_off(void)
{
    digitalWrite(DISPLAY_7SEG_A, LOW);
    digitalWrite(DISPLAY_7SEG_B, LOW);
    digitalWrite(DISPLAY_7SEG_C, LOW);
    digitalWrite(DISPLAY_7SEG_D, LOW);
    digitalWrite(DISPLAY_7SEG_E, LOW);
    digitalWrite(DISPLAY_7SEG_F, LOW);
    digitalWrite(DISPLAY_7SEG_G, LOW);
}

void display7segmentos_print(uint8_t numero)
{
    digitalWrite(DISPLAY_7SEG_A, LOW); // reseteamos todo el display, así ahorramos código después
    digitalWrite(DISPLAY_7SEG_B, LOW);
    digitalWrite(DISPLAY_7SEG_C, LOW);
    digitalWrite(DISPLAY_7SEG_D, LOW);
    digitalWrite(DISPLAY_7SEG_E, LOW);
    digitalWrite(DISPLAY_7SEG_F, LOW);
    digitalWrite(DISPLAY_7SEG_G, LOW);

    switch (numero)
    {
    case 0:
        digitalWrite(DISPLAY_7SEG_A, HIGH);
        digitalWrite(DISPLAY_7SEG_B, HIGH);
        digitalWrite(DISPLAY_7SEG_C, HIGH);
        digitalWrite(DISPLAY_7SEG_D, HIGH);
        digitalWrite(DISPLAY_7SEG_E, HIGH);
        digitalWrite(DISPLAY_7SEG_F, HIGH);
        break;

    case 1:
        digitalWrite(DISPLAY_7SEG_B, HIGH);
        digitalWrite(DISPLAY_7SEG_C, HIGH);
        break;

    case 2:
        digitalWrite(DISPLAY_7SEG_A, HIGH);
        digitalWrite(DISPLAY_7SEG_B, HIGH);
        digitalWrite(DISPLAY_7SEG_D, HIGH);
        digitalWrite(DISPLAY_7SEG_E, HIGH);
        digitalWrite(DISPLAY_7SEG_G, HIGH);
        break;

    case 3:
        digitalWrite(DISPLAY_7SEG_A, HIGH);
        digitalWrite(DISPLAY_7SEG_B, HIGH);
        digitalWrite(DISPLAY_7SEG_C, HIGH);
        digitalWrite(DISPLAY_7SEG_D, HIGH);
        digitalWrite(DISPLAY_7SEG_G, HIGH);
        break;

    case 4:
        digitalWrite(DISPLAY_7SEG_B, HIGH);
        digitalWrite(DISPLAY_7SEG_C, HIGH);
        digitalWrite(DISPLAY_7SEG_F, HIGH);
        digitalWrite(DISPLAY_7SEG_G, HIGH);
        break;

    case 5:
        digitalWrite(DISPLAY_7SEG_A, HIGH);
        digitalWrite(DISPLAY_7SEG_C, HIGH);
        digitalWrite(DISPLAY_7SEG_D, HIGH);
        digitalWrite(DISPLAY_7SEG_F, HIGH);
        digitalWrite(DISPLAY_7SEG_G, HIGH);
        break;

    case 6:
        digitalWrite(DISPLAY_7SEG_A, HIGH);
        digitalWrite(DISPLAY_7SEG_C, HIGH);
        digitalWrite(DISPLAY_7SEG_D, HIGH);
        digitalWrite(DISPLAY_7SEG_E, HIGH);
        digitalWrite(DISPLAY_7SEG_F, HIGH);
        digitalWrite(DISPLAY_7SEG_G, HIGH);
        break;

    case 7:
        digitalWrite(DISPLAY_7SEG_A, HIGH);
        digitalWrite(DISPLAY_7SEG_B, HIGH);
        digitalWrite(DISPLAY_7SEG_C, HIGH);
        break;

    case 8:
        digitalWrite(DISPLAY_7SEG_A, HIGH);
        digitalWrite(DISPLAY_7SEG_B, HIGH);
        digitalWrite(DISPLAY_7SEG_C, HIGH);
        digitalWrite(DISPLAY_7SEG_D, HIGH);
        digitalWrite(DISPLAY_7SEG_E, HIGH);
        digitalWrite(DISPLAY_7SEG_F, HIGH);
        digitalWrite(DISPLAY_7SEG_G, HIGH);
        break;

    case 9:
        digitalWrite(DISPLAY_7SEG_A, HIGH);
        digitalWrite(DISPLAY_7SEG_B, HIGH);
        digitalWrite(DISPLAY_7SEG_C, HIGH);
        digitalWrite(DISPLAY_7SEG_F, HIGH);
        digitalWrite(DISPLAY_7SEG_G, HIGH);
        break;

    case 10:
        digitalWrite(DISPLAY_7SEG_A, HIGH);
        digitalWrite(DISPLAY_7SEG_B, HIGH);
        digitalWrite(DISPLAY_7SEG_C, HIGH);
        digitalWrite(DISPLAY_7SEG_E, HIGH);
        digitalWrite(DISPLAY_7SEG_F, HIGH);
        digitalWrite(DISPLAY_7SEG_G, HIGH);
        break;

    case 11:
        digitalWrite(DISPLAY_7SEG_C, HIGH);
        digitalWrite(DISPLAY_7SEG_D, HIGH);
        digitalWrite(DISPLAY_7SEG_E, HIGH);
        digitalWrite(DISPLAY_7SEG_F, HIGH);
        digitalWrite(DISPLAY_7SEG_G, HIGH);
        break;

    case 12:
        digitalWrite(DISPLAY_7SEG_A, HIGH);
        digitalWrite(DISPLAY_7SEG_D, HIGH);
        digitalWrite(DISPLAY_7SEG_E, HIGH);
        digitalWrite(DISPLAY_7SEG_F, HIGH);
        break;

    case 13:
        digitalWrite(DISPLAY_7SEG_B, HIGH);
        digitalWrite(DISPLAY_7SEG_C, HIGH);
        digitalWrite(DISPLAY_7SEG_D, HIGH);
        digitalWrite(DISPLAY_7SEG_E, HIGH);
        digitalWrite(DISPLAY_7SEG_G, HIGH);
        break;

    case 14:
        digitalWrite(DISPLAY_7SEG_A, HIGH);
        digitalWrite(DISPLAY_7SEG_D, HIGH);
        digitalWrite(DISPLAY_7SEG_E, HIGH);
        digitalWrite(DISPLAY_7SEG_F, HIGH);
        digitalWrite(DISPLAY_7SEG_G, HIGH);
        break;

    case 15:
        digitalWrite(DISPLAY_7SEG_A, HIGH);
        digitalWrite(DISPLAY_7SEG_E, HIGH);
        digitalWrite(DISPLAY_7SEG_F, HIGH);
        digitalWrite(DISPLAY_7SEG_G, HIGH);
        break;

    default:
        break;
    }
}
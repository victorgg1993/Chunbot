#include <Arduino.h>
#include "Display16x2.h"
#include <LiquidCrystal.h>

LiquidCrystal lcd(DISPLAY16x2_PIN_RS, DISPLAY16x2_PIN_E, DISPLAY16x2_PIN_D4, DISPLAY16x2_PIN_D5, DISPLAY16x2_PIN_D6, DISPLAY16x2_PIN_D7);

void display16x2_init(uint8_t lightStatus)
{
    pinMode(DISPLAY16x2_PIN_LED, OUTPUT);
    lcd.begin(16, 2);
    lcd.setCursor(0, 0);
    digitalWrite(DISPLAY16x2_PIN_LED, lightStatus);
}

void display16x2_light(uint8_t status)
{
    digitalWrite(DISPLAY16x2_PIN_LED, status);
}

void display16x2_print(char *texto)
{
    lcd.print(texto);
}

void display16x2_setCursor(uint8_t ejeX, uint8_t ejeY)
{
    lcd.setCursor(ejeX, ejeY);
}

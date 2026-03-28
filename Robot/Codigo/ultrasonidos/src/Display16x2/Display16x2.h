#ifndef _DISPLAY_16x2_
#define _DISPLAY_16x2_

#include <Arduino.h>

#define DISPLAY16x2_PIN_LED 27
#define DISPLAY16x2_PIN_RS 29
#define DISPLAY16x2_PIN_E 31
#define DISPLAY16x2_PIN_D4 33
#define DISPLAY16x2_PIN_D5 35
#define DISPLAY16x2_PIN_D6 37
#define DISPLAY16x2_PIN_D7 39

void display16x2_init(uint8_t lightStatus);
void display16x2_light(uint8_t status);
void display16x2_print(char *texto);
void display16x2_setCursor(uint8_t ejeX, uint8_t ejeY);

#endif
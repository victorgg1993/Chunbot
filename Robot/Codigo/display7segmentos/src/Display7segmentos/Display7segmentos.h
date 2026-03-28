#ifndef DISPLAY_7_SEGMENTOS
#define DISPLAY_7_SEGMENTOS

#include <Arduino.h>

#define DISPLAY_7SEG_A 17
#define DISPLAY_7SEG_B 25
#define DISPLAY_7SEG_C 16
#define DISPLAY_7SEG_D 15
#define DISPLAY_7SEG_E 14
#define DISPLAY_7SEG_F 22
#define DISPLAY_7SEG_G 24

void display7segmentos_init(void);
void display7segmentos_off(void);
void display7segmentos_print(uint8_t numero);

#endif
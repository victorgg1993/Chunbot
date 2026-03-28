#ifndef __OLED__
#define __OLED__

#include <Arduino.h>
#include <Wire.h> // Librería I2C de Arduino

#define PIN_OLED_SDA 20
#define PIN_OLED_SCL 21

// Dirección I2C típica de SSD1315
#define OLED_ADDR 0x3C

void oled_init();
void oled_clear();
void oled_clear_cuadrado(uint8_t x, uint8_t y, uint8_t width, uint8_t height);
void oled_display_text(const char *text, uint8_t x, uint8_t y, uint8_t textSize = 2);
void oled_draw_circle(uint8_t x, uint8_t y, uint8_t radius);
void oled_update();

#endif

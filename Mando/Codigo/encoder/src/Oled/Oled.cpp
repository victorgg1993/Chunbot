#include "Oled.h"

#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// Creamos el objeto SSD1306
Adafruit_SSD1306 display(128, 64, &Wire);

void oled_init()
{
    // Inicializamos I2C (sin parámetros en Arduino Mega)
    Wire.begin();

    // Inicializamos el display
    if (!display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDR))
    {
        Serial.println(F("ERROR: No se pudo iniciar OLED"));
    }
    else
    {
        oled_clear();
    }
}

void oled_clear()
{
    display.clearDisplay();
    oled_update();
}

void oled_clear_cuadrado(uint8_t x, uint8_t y, uint8_t width, uint8_t height)
{
    display.fillRect(x, y, width, height, SSD1306_BLACK);
}

void oled_display_text(const char *text, uint8_t x, uint8_t y, uint8_t textSize = 2)
{
    display.setTextSize(textSize);
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(x, y);
    display.println(text);
}

void oled_draw_circle(uint8_t x, uint8_t y, uint8_t radius)
{
    display.drawCircle(x, y, radius, SSD1306_WHITE); // solo el borde
    // display.fillCircle(x, y, radius, SSD1306_WHITE);   // con relleno
}

void oled_update()
{
    display.display();
}
// plaquita: Arduino mega 2560

#include "src/Oled/Oled.h"
#include "src/SensorTemperatura/SensorTemperatura.h"

void setup()
{
  Serial.begin(9600);

  oled_init();
  sensorTemperatura_init();

  oled_display_text("Chun bot", 14, 0);
  oled_display_text("Temp", 14, 21);
  oled_update();
}

void loop()
{
  float temperatura = sensorTemperatura_read();
  char texto[10];

  dtostrf(temperatura, 5, 2, texto); // ancho 5, 2 decimales
  strcat(texto, " C");

  oled_display_text(":", 60, 23, 2);
  oled_clear_cuadrado(73, 26, 43, 9);
  oled_display_text(texto, 73, 27, 1);
  oled_update();

  delay(1500);
}

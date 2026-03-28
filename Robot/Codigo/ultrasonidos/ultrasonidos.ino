// plaquita: Arduino mega 2560

#include "src/Display16x2/Display16x2.h"
#include "src/HC-SR04/HC-SR04.h"

void setup()
{
  Serial.begin(9600);
  HCSR04_init();
  display16x2_init(HIGH); // Si no quieres luz en la pantalla, ponlo a LOW
}

void loop()
{
  if (HCSR04_isNew())
  {
    float distancia = HCSR04_read();
    char texto[7]; // 6 dígitos + end of string
    dtostrf(distancia, 6, 2, texto); // ancho 6 símbolos + 2 decimales

    display16x2_setCursor(0, 0);
    display16x2_print("Distancia en cm:");
    display16x2_setCursor(0, 1);
    display16x2_print("      "); // limpiar la línea
    display16x2_setCursor(0, 1);
    display16x2_print(texto);
  }

  delay(600);
}

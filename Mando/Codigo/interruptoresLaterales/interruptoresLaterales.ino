// plaquita usada: Arduino nano
#include "src/Oled/Oled.h"
#include "src/Switches/Switches.h"

#define TAMANIO_FUENTE_PEQUENIO 1

void setup()
{
  Serial.begin(9600); // Tools -> Serial Monitor ( 9600 baudios )
  Serial.println("Mando Chunbot");

  oled_init();
  switches_init();

  oled_display_text("Chun Bot", 14, 0);
  oled_display_text("Interr. izq:", 3, 25, TAMANIO_FUENTE_PEQUENIO);
  oled_display_text(valor_switch_izquierdo ? "On " : "Off", 80, 25, TAMANIO_FUENTE_PEQUENIO);

  oled_display_text("Interr. der:", 3, 45, TAMANIO_FUENTE_PEQUENIO);
  oled_display_text(valor_switch_derecho ? "On " : "Off", 80, 45, TAMANIO_FUENTE_PEQUENIO);
  oled_update();
}

void loop()
{
  switches_polling();

  if (switch_izquierdo_cambio())
  {
    oled_clear_cuadrado(78, 25, 20, 7);                                                         // limpiamos el texto anterior de on/off
    oled_display_text(valor_switch_izquierdo ? "On " : "Off", 80, 25, TAMANIO_FUENTE_PEQUENIO); // y pintamos el nuevo
    oled_update();
  }

  if (switch_derecho_cambio())
  {
    oled_clear_cuadrado(78, 45, 20, 7);                                                       // limpiamos el texto anterior de on/off
    oled_display_text(valor_switch_derecho ? "On " : "Off", 80, 45, TAMANIO_FUENTE_PEQUENIO); // y pintamos el nuevo
    oled_update();
  }
}

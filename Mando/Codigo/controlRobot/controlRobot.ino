// plaquita usada: Arduino nano
#include "src/Radio/Radio.h"
#include "src/Oled/Oled.h"
#include "src/Switches/Switches.h"
#include "src/Joystick/Joystick.h"
#include "src/Encoder/Encoder.h"

#define TAMANIO_FUENTE_PEQUENIO 1
#define FILA_1 25 // posición 25 en el eje Y para la fila 1
#define FILA_2 45 // posición 45 en el eje Y para la fila 2

void setup()
{
  Serial.begin(9600);
  Serial.println("Mando Chunbot");

  oled_init();
  switches_init();
  joystick_init();
  nrf_init();
  encoder_init();

  oled_display_text("Chun Bot", 14, 0);
  oled_display_text("Modo mando", 14, FILA_1, TAMANIO_FUENTE_PEQUENIO);
  oled_display_text("radiocontrol", 14, FILA_2, TAMANIO_FUENTE_PEQUENIO);
  oled_update();
}

void loop()
{
  switches_polling(); // interruptores laterales. Aquí también se mandan los estados de los interruptores al robot
  joystick_polling(); // pulsadores + ejes. También se mandan los estados de los interruptores al robot
  nrf_polling();      // módulo de radio
  encoder_polling();  // módulo encoder
}

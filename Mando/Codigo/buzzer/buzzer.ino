// plaquita usada: Arduino nano
#include "src/Buzzer/Buzzer.h"

void setup()
{
  Serial.begin(9600);
  Serial.println("Mando Chunbot");

  buzzer_init();
  buzzer_play_success();
}

void loop()
{
  buzzer_polling(); // de esta forma no se usa delay() y permite no bloquear el código mientras suena la música
}

// plaquita: Arduino mega 2560

#include "src/Buzzer/Buzzer.h"
#include "src/Pulsadores/Pulsadores.h"

void setup()
{
  Serial.begin(9600);

  buzzer_init();
  pulsadores_init();
}

void loop()
{
  buzzer_polling();
  pulsadores_polling();

  if (isUpClicked())
  {
    buzzer_play_startup();
  }

  if (isCenterClicked())
  {
    buzzer_play_error();
  }

  if (isDownClicked())
  {
    buzzer_play_success();
  }
}

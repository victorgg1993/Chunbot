// plaquita: Arduino mega 2560

#include "src/Motores/Motores.h"
#include "src/Radio/Radio.h"
#include "src/Luces/Luces.h"

void setup()
{
  Serial.begin(9600);
  motores_init();
  luces_init();
  nrf_init();
}

void loop()
{
  nrf_polling();
  luces_polling();
  motores_polling();
}

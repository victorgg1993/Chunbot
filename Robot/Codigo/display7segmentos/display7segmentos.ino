// plaquita: Arduino mega 2560

#include "src/Display7segmentos/Display7segmentos.h"
#include "src/Pulsadores/Pulsadores.h"

uint8_t contador = 0;

void setup()
{
  display7segmentos_init();
  pulsadores_init();
  display7segmentos_print(contador);
}

void loop()
{
  pulsadores_polling();

  if (isLeftClicked())
  {
    // no dejamos negativos. Si llegamos al 0, volvemos al 15
    if (contador > 0)
    {
      contador--;
    }
    else
    {
      contador = 15;
    }

    display7segmentos_print(contador);
  }

  if (isRightClicked())
  {
    contador++;
    contador %= 16; // del 0 al 15
    display7segmentos_print(contador);
  }
}

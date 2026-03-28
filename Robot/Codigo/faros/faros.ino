// plaquita: Arduino mega 2560

#include "src/Luces/Luces.h"
#include "src/Pulsadores/Pulsadores.h"

bool estadoLuces = false;

void setup()
{
    luces_init();
    pulsadores_init();
}

void loop()
{
    pulsadores_polling();

    if (isCenterClicked())
    {
        estadoLuces = !estadoLuces; // forma simple de invertir el estado
        luces_write(estadoLuces ? HIGH : LOW);
    }
}

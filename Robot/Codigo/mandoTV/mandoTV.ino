// plaquita: Arduino mega 2560

#include "src/Display16x2/Display16x2.h"
#include "src/NEC32/NEC32.h"

uint32_t codigoLeido = 0;
uint32_t codigoAnterior = 0;

void pintarCodigoPorPantalla(void);
void gestionarTeclas(void);

void setup()
{
  display16x2_init(HIGH); // Si no quieres luz en el display, ponlo en LOW
  NEC32_init();
}

void loop()
{
  NEC32_update();

  // Solamente imprimir cuando hay nuevo código ( puede ser el mismo código pero entró de nuevo, por lo que se considera un nuevo código )
  if (NEC32_isNew())
  {
    codigoLeido = NEC32_read();

    // Aquí se vigila que si el código es el mismo que el anterior, se ignore
    if (codigoLeido != codigoAnterior)
    {
      display16x2_setCursor(0, 0);
      display16x2_print("Codigo:");

      pintarCodigoPorPantalla();
      gestionarTeclas();

      codigoAnterior = codigoLeido;
    }
  }
}

void pintarCodigoPorPantalla(void)
{
  char texto[11];
  sprintf(texto, "%06lX", codigoLeido);
  display16x2_print(texto);
}

void gestionarTeclas(void)
{
  switch (codigoLeido)
  {
    // El botón nº1 enciende la luz del display
  case NEC32_1:
    display16x2_light(HIGH);
    break;

    // El botón nº0 la apaga
  case NEC32_0:
    display16x2_light(LOW);
    break;

  default:
    break;
  }
}

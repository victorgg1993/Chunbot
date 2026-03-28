// plaquita: Arduino mega 2560

#include "src/Display16x2/Display16x2.h"
#include "src/Pulsadores/Pulsadores.h"

void codigo_prueba_setup(void);
void codigo_prueba_loop(void);

void setup()
{
  Serial.begin(9600);
  pulsadores_init();
  display16x2_init(HIGH); // ponlo a LOW para apagar la luz de la pantalla

  display16x2_setCursor(0, 0);
  display16x2_print("Boton:");
}

void loop()
{
  pulsadores_polling();

  if (isUpClicked())
  {
    display16x2_setCursor(6, 0);
    display16x2_print("Up    "); // el espacio en blanco es para limpiar el valor anterior
  }

  if (isCenterlicked())
  {
    display16x2_setCursor(6, 0);
    display16x2_print("Center");
  }

  if (isDownClicked())
  {
    display16x2_setCursor(6, 0);
    display16x2_print("Down   "); // el espacio en blanco es para limpiar el valor anterior
  }

  if (isLeftClicked())
  {
    display16x2_setCursor(6, 0);
    display16x2_print("Left   "); // el espacio en blanco es para limpiar el valor anterior
  }

  if (isRightClicked())
  {
    display16x2_setCursor(6, 0);
    display16x2_print("Right  "); // el espacio en blanco es para limpiar el valor anterior
  }
}

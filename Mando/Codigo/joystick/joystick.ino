// plaquita usada: Arduino nano
#include "src/Oled/Oled.h"
#include "src/Joystick/Joystick.h"

#define NUMERO_DIGITOS 5
#define TAMANIO_FUENTE_PEQUENIO 1
#define FILA_1 25 // posición 25 en el eje Y para la fila 1
#define FILA_2 45 // posición 45 en el eje Y para la fila 2

uint8_t contador_clicks_izquierdo = 0;
uint8_t contador_clicks_derecho = 0;

unsigned long tiempoAnterior = 0;
unsigned long tiempoActual = millis();

void setup()
{
  Serial.begin(9600);
  Serial.println("Mando Chunbot");

  oled_init();
  joystick_init();

  oled_display_text("Chun Bot", 14, 0);
  oled_display_text("Izq:", 5, FILA_1, TAMANIO_FUENTE_PEQUENIO);
  oled_display_text("Der:", 5, FILA_2, TAMANIO_FUENTE_PEQUENIO);

  oled_display_text("Cont:", 70, FILA_1, TAMANIO_FUENTE_PEQUENIO);
  oled_display_text("0", 105, FILA_1, TAMANIO_FUENTE_PEQUENIO);

  oled_display_text("Cont:", 70, FILA_2, TAMANIO_FUENTE_PEQUENIO);
  oled_display_text("0", 105, FILA_2, TAMANIO_FUENTE_PEQUENIO);
}

void loop()
{
  joystick_polling(); // pulsadores + ejes.

  if (joystick_isLeftClicked())
  {
    contador_clicks_izquierdo++;
    contador_clicks_izquierdo %= 10; // del 0 al 9

    String texto = String(contador_clicks_izquierdo);
    oled_clear_cuadrado(105, FILA_1, 5, 8); // limpiamos antes de pintar el nuevo valor
    oled_display_text(texto.c_str(), 105, FILA_1, TAMANIO_FUENTE_PEQUENIO);
  }

  if (joystick_isRightClicked())
  {
    contador_clicks_derecho++;
    contador_clicks_derecho %= 10; // del 0 al 9

    String texto = String(contador_clicks_derecho);
    oled_clear_cuadrado(105, FILA_2, 5, 8); // limpiamos antes de pintar el nuevo valor
    oled_display_text(texto.c_str(), 105, FILA_2, TAMANIO_FUENTE_PEQUENIO);
  }

  // Cada 100ms refrescamos los valores del joystick.
  // No se usa delay() porque es bloqueante. Con este sistema se puede seguir usando el chip sin bloquear.
  tiempoActual = millis();
  if (tiempoActual - tiempoAnterior >= 100)
  {
    tiempoAnterior = tiempoActual;

    pintarJoystickIzquierdo();
    pintarJoystickDerecho();

    oled_update(); // aquí es donde realmente se refresca la pantalla ( así es más rápido todo. Todo lo anterior tocaba la ram )
  }
}

void pintarJoystickIzquierdo(void)
{
  char textoJoystickLY[NUMERO_DIGITOS];
  convertir_a_string(joystickLY, textoJoystickLY);
  oled_clear_cuadrado(30, FILA_1, 24, 8); // limpiamos antes de pintar el nuevo valor
  oled_display_text(textoJoystickLY, 30, FILA_1, TAMANIO_FUENTE_PEQUENIO);
}

void pintarJoystickDerecho(void)
{
  char textoJoystickRY[NUMERO_DIGITOS];
  convertir_a_string(joystickRY, textoJoystickRY);
  oled_clear_cuadrado(30, FILA_2, 24, 8); // limpiamos antes de pintar el nuevo valor
  oled_display_text(textoJoystickRY, 30, FILA_2, TAMANIO_FUENTE_PEQUENIO);
}

void convertir_a_string(uint16_t numero, char *texto)
{
  snprintf(texto, NUMERO_DIGITOS, "%04u", numero); // el número siempre tendrá 4 dígitos
}
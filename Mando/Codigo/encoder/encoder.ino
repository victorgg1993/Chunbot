// plaquita usada: Arduino nano
#include "src/Oled/Oled.h"
#include "src/Encoder/Encoder.h"

#define NUMERO_DIGITOS 4
#define TAMANIO_FUENTE_PEQUENIO 1
#define FILA_1 25 // posición 25 en el eje Y para la fila 1

uint8_t contador_clicks = 0;

void setup()
{
  Serial.begin(9600);
  Serial.println("Mando Chunbot");

  oled_init();
  encoder_init();

  oled_display_text("Chun Bot", 14, 0);
  oled_display_text("Enc:", 5, FILA_1, TAMANIO_FUENTE_PEQUENIO);
  oled_display_text("000", 30, FILA_1, TAMANIO_FUENTE_PEQUENIO);

  oled_display_text("Cont:", 70, FILA_1, TAMANIO_FUENTE_PEQUENIO);
  oled_display_text("0", 105, FILA_1, TAMANIO_FUENTE_PEQUENIO);

  oled_update();
}

void loop()
{
  encoder_polling(); // pulsadores + ejes.

  // Detectar rotación encoder
  if (encoder_hasChanged())
  {
    int8_t position = encoder_getPosition();

    char textoEncoderPos[NUMERO_DIGITOS];
    convertir_a_string(position, textoEncoderPos);
    oled_clear_cuadrado(30, FILA_1, 24, 8); // limpiamos antes de pintar el nuevo valor
    oled_display_text(textoEncoderPos, 30, FILA_1, TAMANIO_FUENTE_PEQUENIO);

    oled_update();
  }

  if (encoder_switch_isClicked())
  {
    contador_clicks++;
    contador_clicks %= 10; // del 0 al 9

    String texto = String(contador_clicks);
    oled_clear_cuadrado(105, FILA_1, 5, 8); // limpiamos antes de pintar el nuevo valor
    oled_display_text(texto.c_str(), 105, FILA_1, TAMANIO_FUENTE_PEQUENIO);
    oled_update();
  }
}

void convertir_a_string(uint8_t numero, char *texto)
{
  snprintf(texto, NUMERO_DIGITOS, "%03u", numero); // el número siempre tendrá 4 dígitos
}
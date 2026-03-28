#ifndef _NEC32_H_
#define _NEC32_H_

#include <Arduino.h>

#define NEC32_PIN 4

// códigos de las teclas
#define NEC32_1 0xFFA25D
#define NEC32_2 0xFF629D
#define NEC32_3 0xFFE21D
#define NEC32_4 0xFF22DD
#define NEC32_5 0xFF02FD
#define NEC32_6 0xFFC23D
#define NEC32_7 0xFFE01F
#define NEC32_8 0xFFA857
#define NEC32_9 0xFF906F
#define NEC32_0 0xFF9867
#define NEC32_ASTERISCO 0xFF6897
#define NEC32_ALMOHADILLA 0xFFB04F
#define NEC32_HASHTAG 0xFFB04F
#define NEC32_UP 0xFF18E7
#define NEC32_DOWN 0xFF4AB5
#define NEC32_LEFT 0xFF10EF
#define NEC32_RIGHT 0xFF5AA5
#define NEC32_OK 0xFF38C7

// Inicialización
void NEC32_init(void);

void NEC32_update(void);   // debe llamarse en loop
bool NEC32_isNew(void);
uint32_t NEC32_read(void);

// Depuración
void NEC32_debug(void);

#endif

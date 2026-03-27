#ifndef __SWITCHES_H__
#define __SWITCHES_H__

#include <Arduino.h>

#define PIN_SWITCH_IZQUIERDO 6
#define PIN_SWITCH_DERECHO 5

// Para poder usarse desde fuera
extern bool valor_switch_izquierdo;
extern bool valor_switch_derecho;

void switches_init(void);
void switches_polling(void);
bool switch_izquierdo_cambio(void);
bool switch_derecho_cambio(void);
bool switch_izquierdo_activado(void);
bool switch_izquierdo_desactivado(void);
bool switch_derecho_activado(void);
bool switch_derecho_desactivado(void);

void _switch_readAll(void);
void _switch_readIzq(unsigned long ahora);
void _switch_readDer(unsigned long ahora);

#endif

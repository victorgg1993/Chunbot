#include <Arduino.h>

#include "globals.h"

// ----------------------------------------------------------------------- interruptor izquierdo
bool cambio_switch_izquierdo = false;
bool estado_switch_izquierdo = LOW;
bool estado_switch_izquierdo_anterior = LOW;

// ----------------------------------------------------------------------- interruptor derecho
bool cambio_switch_derecho = false;
bool estado_switch_derecho = LOW;
bool estado_switch_derecho_anterior = LOW;

// ----------------------------------------------------------------------- joystick izquierdo
bool cambio_joystick_izquierdoY = false;
uint16_t valor_joystick_izquierdoY = 0;
uint16_t valor_joystick_izquierdoY_anterior = 0;

// ----------------------------------------------------------------------- joystick derecho
bool cambio_joystick_derechoY = false;
uint16_t valor_joystick_derechoY = 0;
uint16_t valor_joystick_derechoY_anterior = 0;

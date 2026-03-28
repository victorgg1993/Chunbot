#ifndef _GLOBALS_H_
#define _GLOBALS_H_

#define POS_JOYLYL 0
#define POS_JOYLYH 1
#define POS_JOYRYL 2
#define POS_JOYRYH 3
#define POS_SWL 4
#define POS_SWR 5

// Motores ( márgenes de la lectura del joystick recibidos )
#define ZONA_MUERTA_INF 1013
#define ZONA_MUERTA_SUP 1023

#define MOTOR_IZQUIERDO 0
#define MOTOR_DERECHO 1

// NRF24L01 ( radio )
#define PACKET_TIMEOUT 100 // ms
#define BUFFER_SIZE 64
#define TIMEOUT_MS 50

extern bool cambio_switch_izquierdo;
extern bool estado_switch_izquierdo;
extern bool estado_switch_izquierdo_anterior;

extern bool cambio_switch_derecho;
extern bool estado_switch_derecho;
extern bool estado_switch_derecho_anterior;

extern bool cambio_joystick_izquierdoY;
extern uint16_t valor_joystick_izquierdoY;
extern uint16_t valor_joystick_izquierdoY_anterior;

extern bool cambio_joystick_derechoY;
extern uint16_t valor_joystick_derechoY;
extern uint16_t valor_joystick_derechoY_anterior;

#endif

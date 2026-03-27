#ifndef __RADIO_H_
#define __RADIO_H_

#include <Arduino.h>

#define PIN_RADIO_CE 9
#define PIN_RADIO_CSN 10

#define POS_JOYLYL 0
#define POS_JOYLYH 1
#define POS_JOYRYL 2
#define POS_JOYRYH 3
#define POS_SWL 4
#define POS_SWR 5

#define LADO_L 4 // ha de coincidir con POS_SWL
#define LADO_R 5 // ha de coincidir con POS_SWR

void nrf_init(void);
void nrf_polling(void);

void nrf_send_joystick_izqX(uint16_t eje_x);
void nrf_send_joystick_izqY(uint16_t eje_y);
void nrf_send_joystick_derX(uint16_t eje_x);
void nrf_send_joystick_derY(uint16_t eje_y);

void nrf_send_switch(char lado, bool estado);

#endif

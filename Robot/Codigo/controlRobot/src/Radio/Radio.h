#ifndef __RADIO_H_
#define __RADIO_H_

#include <Arduino.h>

#define SIZE_PAQUETE 32

#define PIN_RADIO_CE 43
#define PIN_RADIO_CSN 53
#define PIN_RADIO_IRQ 18

void nrf_init(void);
void nrf_polling(void);

void _nrf_procesar_paquete(uint8_t *data, uint8_t length);
void _nrf_hard_reset(void);
uint16_t _nrf_joystick_izquierdo(uint16_t valorLeido);
uint16_t _nrf_joystick_derecho(uint16_t valorLeido);
#endif

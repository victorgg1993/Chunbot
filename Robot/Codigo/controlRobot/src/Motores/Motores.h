#ifndef _MOTORES_
#define _MOTORES_

#include <Arduino.h>

#define PIN_MOTOR_IZQUIERDO 8
#define PIN_MOTOR_DERECHO 12
#define PWM_VELOCIDAD_ADELANTE 128 // 180 = máxima ; 91 = mínima
#define PWM_STOP 90
#define PWM_VELOCIDAD_ATRAS 52 // 0 = máxima ; 89 = mínima

#define VALOR_MAX_UP 2000     // Máximo up
#define VALOR_MIN_UP 1510     // Mínimo up (empieza a funcionar)
#define VALOR_CENTRO_SUP 1509 // Límite superior zona muerta
#define VALOR_CENTRO_INF 1491 // Límite inferior zona muerta
#define VALOR_MIN_DOWN 1000   // Máximo down
#define VALOR_MAX_DOWN 1490   // Mínimo down (empieza a funcionar)

#define UP_MIN 1510
#define UP_MAX 2000
#define DOWN_MIN 1000
#define DOWN_MAX 1490

#define MAP_SERVO_GRADOS_A_PULSOS(valor) map(valor, 0, 180, 750, 2250)

#define STOP 0
#define ADELANTE 1
#define DERECHA 2
#define IZQUIERDA 3
#define ATRAS 4

#define MOTOR_IZQUIERDO 1
#define MOTOR_DERECHO 0

void motores_init(void);
void motores_off(void);
void motores_go(uint8_t direccion);
void motor_runProporcional(uint8_t motor, uint16_t valor);
void motores_polling(void);

#endif
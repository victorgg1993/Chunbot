#include <Arduino.h>
#include "../globals.h"
#include "Motores.h"
#include <ServoTimer2.h>

ServoTimer2 servoIzquierdo;
ServoTimer2 servoDerecho;

void motores_init(void)
{
    servoIzquierdo.attach(PIN_MOTOR_IZQUIERDO);
    servoDerecho.attach(PIN_MOTOR_DERECHO);

    motores_off();
}

void motores_off(void)
{
    servoIzquierdo.write(MAP_SERVO_GRADOS_A_PULSOS(PWM_STOP));
    servoDerecho.write(MAP_SERVO_GRADOS_A_PULSOS(PWM_STOP));
}

void motores_go(uint8_t direccion)
{
    switch (direccion)
    {
    case ADELANTE:
        servoIzquierdo.write(MAP_SERVO_GRADOS_A_PULSOS(PWM_VELOCIDAD_ATRAS));
        servoDerecho.write(MAP_SERVO_GRADOS_A_PULSOS(PWM_VELOCIDAD_ADELANTE));
        break;

    case DERECHA:
        servoIzquierdo.write(MAP_SERVO_GRADOS_A_PULSOS(PWM_VELOCIDAD_ADELANTE));
        break;

    case IZQUIERDA:
        servoDerecho.write(MAP_SERVO_GRADOS_A_PULSOS(PWM_VELOCIDAD_ATRAS));
        break;

    case ATRAS:
        servoIzquierdo.write(MAP_SERVO_GRADOS_A_PULSOS(PWM_VELOCIDAD_ATRAS));
        servoDerecho.write(MAP_SERVO_GRADOS_A_PULSOS(PWM_VELOCIDAD_ADELANTE));
        break;

    case STOP:
    default:
        motores_off();
        break;
    }
}

void motor_runProporcional(uint8_t motor, uint16_t valor)
{
    if (motor == MOTOR_IZQUIERDO)
    {
        servoIzquierdo.write(MAP_SERVO_GRADOS_A_PULSOS(valor));
    }
    else
    {
        servoDerecho.write(MAP_SERVO_GRADOS_A_PULSOS(valor));
    }
}

void motores_polling(void)
{
    if (cambio_joystick_izquierdoY)
    {
        motor_runProporcional(MOTOR_IZQUIERDO, valor_joystick_izquierdoY);
        cambio_joystick_izquierdoY = false;
    }

    if (cambio_joystick_derechoY)
    {
        motor_runProporcional(MOTOR_DERECHO, valor_joystick_derechoY);
        cambio_joystick_derechoY = false;
    }
}
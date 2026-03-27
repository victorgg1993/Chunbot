#ifndef __JOYSTICK_H__
#define __JOYSTICK_H__

#include <Arduino.h>

// Margen +- para que no esté enviando datos si el valor cambió de 243 a 242
#define JOYSTICK_MARGEN 18
#define JOYSTICK_VALOR_CENTRAL 500

#define JOYSTICK_BUTTON_LEFT 7
#define JOYSTICK_BUTTON_RIGHT 8

#define DEBOUNCE_DELAY 50

// Para poder usarse desde fuera
extern uint16_t joystickLY;
extern uint16_t joystickRY;

// Estados de los pulsadores
typedef struct
{
    bool leftButtonPressed;
    bool rightButtonPressed;
    bool leftButtonLastState;
    bool rightButtonLastState;
    unsigned long lastDebounceTimeLeft;
    unsigned long lastDebounceTimeRight;
} joystick_buttons_t;

void joystick_init(void);
void joystick_polling(void);
uint16_t mapearJoystick(int16_t valor);
void joystick_updateButtons(void);
bool joystick_isLeftPressed(void);
bool joystick_isRightPressed(void);
bool joystick_isLeftClicked(void);
bool joystick_isRightClicked(void);

#endif
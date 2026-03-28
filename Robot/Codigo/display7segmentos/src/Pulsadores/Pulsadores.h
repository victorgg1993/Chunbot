#ifndef _PULSADORES_
#define _PULSADORES_

#include <Arduino.h>

#define PULSADOR_FISICO_UP A12
#define PULSADOR_FISICO_DOWN A8
#define PULSADOR_FISICO_LEFT A11
#define PULSADOR_FISICO_RIGHT A9
#define PULSADOR_FISICO_OK A10

#define PULSADOR_UP 1
#define PULSADOR_DOWN 2
#define PULSADOR_LEFT 3
#define PULSADOR_RIGHT 4
#define PULSADOR_OK 5

// Configuración de debounce (ms)
#define BUTTON_DEBOUNCE_DELAY 50

// Estructura para almacenar el estado de un pulsador
typedef struct
{
    bool pressed;                   // Estado actual presionado
    bool lastState;                 // Último estado para detección de flancos
    unsigned long lastDebounceTime; // Último tiempo para debounce
} button_state_t;

// Estructura para todos los pulsadores
typedef struct
{
    button_state_t up;
    button_state_t down;
    button_state_t left;
    button_state_t right;
    button_state_t ok;
} pulsadores_state_t;

// Inicialización
void pulsadores_init(void);

// Actualización de estados (llamar en el loop)
void pulsadores_polling(void);

// Funciones para consultar estados
bool button_isPressed(uint8_t buttonPin);
bool button_isClicked(uint8_t buttonPin);
bool button_isReleased(uint8_t buttonPin);

// Funciones específicas para cada pulsador (más cómodo)
bool isUpPressed(void);
bool isUpClicked(void);
bool isDownPressed(void);
bool isDownClicked(void);
bool isLeftPressed(void);
bool isLeftClicked(void);
bool isRightPressed(void);
bool isRightClicked(void);
bool isCenterPressed(void);
bool isCenterClicked(void);

// Función para obtener cualquier pulsador presionado (útil para menús)
uint8_t getAnyButtonPressed(void);
uint8_t getAnyButtonClicked(void);

#endif
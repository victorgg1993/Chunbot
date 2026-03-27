#ifndef __ENCODER_H__
#define __ENCODER_H__

#include <Arduino.h>

// Definición de pines
#define ENCODER_PIN_A 2  // Canal A (interrupción 0 en Arduino Nano)
#define ENCODER_PIN_B 3  // Canal B (interrupción 1 en Arduino Nano)
#define ENCODER_PIN_SW 4 // Pulsador (polling)

// Configuración de debounce
#define ENCODER_DEBOUNCE_DELAY_MS 5 // Debounce para encoder (ms)
#define ENCODER_SW_DEBOUNCE_MS 50   // Debounce para pulsador (ms)

// Estructura para almacenar el estado del encoder
typedef struct
{
    volatile int32_t position;               // Posición actual (contador)
    volatile int32_t lastPosition;           // Última posición reportada
    volatile uint8_t lastEncoded;            // Último estado codificado
    volatile unsigned long lastDebounceTime; // Último tiempo para debounce
    volatile bool changed;                   // Flag de cambio
} encoder_state_t;

// Estructura para el pulsador
typedef struct
{
    bool pressed;                   // Estado actual presionado
    bool lastPressed;               // Último estado
    bool clicked;                   // Flag de click (flanco de bajada)
    unsigned long lastDebounceTime; // Último tiempo para debounce
} encoder_switch_t;

// Inicialización
void encoder_init(void);

// Funciones de actualización (llamar en loop)
void encoder_polling(void); // Actualiza estados (para polling del pulsador)
void encoder_reset(void);  // Reinicia el contador a 0

// Funciones para obtener valores
int32_t encoder_getPosition(void); // Obtiene posición actual
int32_t encoder_getDelta(void);    // Obtiene el cambio desde la última lectura
bool encoder_hasChanged(void);     // Indica si hubo cambio desde última lectura
bool encoder_isTurning(void);      // Indica si se está girando

// Funciones para el pulsador
bool encoder_switch_isPressed(void); // Retorna true si está presionado ahora
bool encoder_switch_isClicked(void); // Retorna true cuando se suelta el pulsador
bool encoder_switch_isHeld(void);    // Retorna true si está presionado por más tiempo

// Función de callback para interrupciones (no llamar directamente)
void encoder_handleInterrupt(void);

#endif
#ifndef __ENCODER_H__
#define __ENCODER_H__

#include <Arduino.h>

// Pines
#define ENCODER_PIN_A 2
#define ENCODER_PIN_B 3
#define ENCODER_PIN_SW 4

// Debounce
#define ENCODER_DEBOUNCE_DELAY_MS 5
#define ENCODER_SW_DEBOUNCE_MS 50

// ---------------- ENCODER ----------------
typedef struct
{
    volatile int8_t position;          // ← 8 bits
    volatile int8_t lastPosition;      // ← 8 bits
    volatile uint8_t lastEncoded;
    volatile unsigned long lastDebounceTime;
    volatile bool changed;
} encoder_state_t;

// ---------------- SWITCH ----------------
typedef struct
{
    bool pressed;
    bool lastPressed;
    bool clicked;
    unsigned long lastDebounceTime;
} encoder_switch_t;

// Inicialización
void encoder_init(void);
void encoder_polling(void);
void encoder_reset(void);

// Lectura
int8_t encoder_getPosition(void);
int8_t encoder_getDelta(void);
bool encoder_hasChanged(void);
bool encoder_isTurning(void);

// Pulsador
bool encoder_switch_isPressed(void);
bool encoder_switch_isClicked(void);
bool encoder_switch_isHeld(void);

// ISR
void encoder_handleInterrupt(void);

#endif
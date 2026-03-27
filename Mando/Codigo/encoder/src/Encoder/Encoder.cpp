#include "Encoder.h"
#include <limits.h>

// -----------------------------------------------------------------------------
// Estado del encoder
// -----------------------------------------------------------------------------
static encoder_state_t encoder = {
    .position = 0,
    .lastPosition = 0,
    .lastEncoded = 0,
    .lastDebounceTime = 0,
    .changed = false};

// -----------------------------------------------------------------------------
// Estado del pulsador
// -----------------------------------------------------------------------------
static encoder_switch_t encoderSwitch = {
    .pressed = false,
    .lastPressed = false,
    .clicked = false,
    .lastDebounceTime = 0};

// -----------------------------------------------------------------------------
// Constantes
// -----------------------------------------------------------------------------
static const unsigned long HOLD_TIME_MS = 1000;

// Tabla de estados (Gray code)
static const int8_t encoderStates[16] = {
    0, -1, 1, 0,
    1, 0, 0, -1,
    -1, 0, 0, 1,
    0, 1, -1, 0};

// -----------------------------------------------------------------------------
// ISR del encoder
// -----------------------------------------------------------------------------
void encoder_handleInterrupt(void)
{
    unsigned long currentTime = millis();

    // Debounce básico
    if ((currentTime - encoder.lastDebounceTime) < ENCODER_DEBOUNCE_DELAY_MS)
        return;

    encoder.lastDebounceTime = currentTime;

    uint8_t stateA = digitalRead(ENCODER_PIN_A);
    uint8_t stateB = digitalRead(ENCODER_PIN_B);

    uint8_t currentState = (stateA << 1) | stateB;
    uint8_t combinedState = (encoder.lastEncoded << 2) | currentState;

    int8_t change = encoderStates[combinedState];

    // 🔁 INVERTIR SENTIDO DEL GIRO
    change = -change;

    if (change != 0)
    {
        // Saturación INT8
        if (!((encoder.position == INT8_MAX && change > 0) ||
              (encoder.position == INT8_MIN && change < 0)))
        {
            encoder.position += change;
        }
        encoder.changed = true;
    }

    encoder.lastEncoded = currentState;
}

// -----------------------------------------------------------------------------
// Inicialización
// -----------------------------------------------------------------------------
void encoder_init(void)
{
    pinMode(ENCODER_PIN_A, INPUT_PULLUP);
    pinMode(ENCODER_PIN_B, INPUT_PULLUP);
    pinMode(ENCODER_PIN_SW, INPUT_PULLUP);

    uint8_t stateA = digitalRead(ENCODER_PIN_A);
    uint8_t stateB = digitalRead(ENCODER_PIN_B);

    encoder.lastEncoded = (stateA << 1) | stateB;
    encoder.position = 0;
    encoder.lastPosition = 0;
    encoder.changed = false;

    attachInterrupt(digitalPinToInterrupt(ENCODER_PIN_A),
                    encoder_handleInterrupt, CHANGE);
    attachInterrupt(digitalPinToInterrupt(ENCODER_PIN_B),
                    encoder_handleInterrupt, CHANGE);
}

// -----------------------------------------------------------------------------
// Polling del pulsador
// -----------------------------------------------------------------------------
void encoder_polling(void)
{
    unsigned long currentTime = millis();
    bool currentPressed = (digitalRead(ENCODER_PIN_SW) == LOW);

    if (currentPressed != encoderSwitch.lastPressed)
        encoderSwitch.lastDebounceTime = currentTime;

    if ((currentTime - encoderSwitch.lastDebounceTime) > ENCODER_SW_DEBOUNCE_MS)
    {
        if (currentPressed != encoderSwitch.pressed)
        {
            if (encoderSwitch.pressed && !currentPressed)
                encoderSwitch.clicked = true;

            encoderSwitch.pressed = currentPressed;
        }
    }

    encoderSwitch.lastPressed = currentPressed;
}

// -----------------------------------------------------------------------------
// Utilidades
// -----------------------------------------------------------------------------
void encoder_reset(void)
{
    noInterrupts();
    encoder.position = 0;
    encoder.changed = true;
    interrupts();
}

int8_t encoder_getPosition(void)
{
    int8_t pos;
    noInterrupts();
    pos = encoder.position;
    interrupts();
    return pos;
}

int8_t encoder_getDelta(void)
{
    int8_t delta;
    noInterrupts();
    delta = encoder.position - encoder.lastPosition;
    encoder.lastPosition = encoder.position;
    interrupts();
    return delta;
}

bool encoder_hasChanged(void)
{
    bool changed;
    noInterrupts();
    changed = encoder.changed;
    encoder.changed = false;
    interrupts();
    return changed;
}

bool encoder_isTurning(void)
{
    return encoder_hasChanged();
}

// -----------------------------------------------------------------------------
// Pulsador
// -----------------------------------------------------------------------------
bool encoder_switch_isPressed(void)
{
    return encoderSwitch.pressed;
}

bool encoder_switch_isClicked(void)
{
    bool clicked = encoderSwitch.clicked;
    encoderSwitch.clicked = false;
    return clicked;
}

bool encoder_switch_isHeld(void)
{
    static unsigned long pressStartTime = 0;
    static bool wasPressed = false;

    if (encoderSwitch.pressed && !wasPressed)
        pressStartTime = millis();

    wasPressed = encoderSwitch.pressed;

    return (encoderSwitch.pressed &&
            (millis() - pressStartTime) > HOLD_TIME_MS);
}
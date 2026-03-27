#include "Encoder.h"

// Variables estáticas para el encoder
static encoder_state_t encoder = {
    .position = 0,
    .lastPosition = 0,
    .lastEncoded = 0,
    .lastDebounceTime = 0,
    .changed = false};

// Variables estáticas para el pulsador
static encoder_switch_t encoderSwitch = {
    .pressed = false,
    .lastPressed = false,
    .clicked = false,
    .lastDebounceTime = 0
    //
};

// Constante para detección de presión prolongada (ms)
static const unsigned long HOLD_TIME_MS = 1000;

// Tabla de estados para decodificación del encoder
// Esta tabla mapea las transiciones de los estados (A, B)
// Formato: estado anterior (bits 2-3) y estado actual (bits 0-1)
// Retorna: -1 = giro antihorario, 0 = sin cambio, 1 = giro horario
static const int8_t encoderStates[] = {
    0,  // 0000 (0)
    -1, // 0001 (1) - Antihorario
    1,  // 0010 (2) - Horario
    0,  // 0011 (3)
    1,  // 0100 (4) - Horario
    0,  // 0101 (5)
    0,  // 0110 (6)
    -1, // 0111 (7) - Antihorario
    -1, // 1000 (8) - Antihorario
    0,  // 1001 (9)
    0,  // 1010 (10)
    1,  // 1011 (11) - Horario
    0,  // 1100 (12)
    1,  // 1101 (13) - Horario
    -1, // 1110 (14) - Antihorario
    0   // 1111 (15)
};

// Función de interrupción
void encoder_handleInterrupt(void)
{
    unsigned long currentTime = millis();

    // Debounce para evitar lecturas erróneas
    if ((currentTime - encoder.lastDebounceTime) < ENCODER_DEBOUNCE_DELAY_MS)
    {
        return;
    }
    encoder.lastDebounceTime = currentTime;

    // Leer estados actuales de los pines A y B
    uint8_t stateA = digitalRead(ENCODER_PIN_A);
    uint8_t stateB = digitalRead(ENCODER_PIN_B);

    // Codificar estado actual (bits: bit0 = A, bit1 = B)
    uint8_t currentState = (stateA << 1) | stateB;

    // Combinar estado anterior (bits 2-3) con estado actual (bits 0-1)
    uint8_t combinedState = (encoder.lastEncoded << 2) | currentState;

    // Obtener cambio de la tabla
    int8_t change = encoderStates[combinedState];

    // Actualizar posición si hay cambio
    if (change != 0)
    {
        encoder.position += change;
        encoder.changed = true;
    }

    // Guardar estado actual para próxima interrupción
    encoder.lastEncoded = currentState;
}

void encoder_init(void)
{
    // Configurar pines del encoder
    pinMode(ENCODER_PIN_A, INPUT_PULLUP);
    pinMode(ENCODER_PIN_B, INPUT_PULLUP);
    pinMode(ENCODER_PIN_SW, INPUT_PULLUP);

    // Leer estado inicial
    uint8_t stateA = digitalRead(ENCODER_PIN_A);
    uint8_t stateB = digitalRead(ENCODER_PIN_B);
    encoder.lastEncoded = (stateA << 1) | stateB;
    encoder.position = 0;
    encoder.lastPosition = 0;
    encoder.changed = false;

    // Configurar interrupciones para ambos pines
    // En Arduino Nano: pin 2 = INT0, pin 3 = INT1
    attachInterrupt(digitalPinToInterrupt(ENCODER_PIN_A), encoder_handleInterrupt, CHANGE);
    attachInterrupt(digitalPinToInterrupt(ENCODER_PIN_B), encoder_handleInterrupt, CHANGE);
}

void encoder_polling(void)
{
    unsigned long currentTime = millis();

    // Leer estado actual del pulsador (LOW = presionado por pull-up)
    bool currentPressed = (digitalRead(ENCODER_PIN_SW) == LOW);

    // Debounce
    if (currentPressed != encoderSwitch.lastPressed)
    {
        encoderSwitch.lastDebounceTime = currentTime;
    }

    if ((currentTime - encoderSwitch.lastDebounceTime) > ENCODER_SW_DEBOUNCE_MS)
    {
        // Solo actualizar si el estado es diferente al actual
        if (currentPressed != encoderSwitch.pressed)
        {
            // Detectar flanco de subida (cuando se suelta el pulsador)
            // Si estaba presionado y ahora no, es un click
            if (encoderSwitch.pressed == true && currentPressed == false)
            {
                encoderSwitch.clicked = true;
            }

            // Actualizar estado
            encoderSwitch.pressed = currentPressed;
        }
    }

    // Guardar último estado para debounce
    encoderSwitch.lastPressed = currentPressed;
}

void encoder_reset(void)
{
    noInterrupts(); // Deshabilitar interrupciones temporalmente
    encoder.position = 0;
    encoder.changed = true;
    interrupts(); // Rehabilitar interrupciones
}

int32_t encoder_getPosition(void)
{
    int32_t pos;
    noInterrupts(); // Leer variable volátil de forma segura
    pos = encoder.position;
    interrupts();
    return pos;
}

int32_t encoder_getDelta(void)
{
    int32_t delta;
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
    encoder.changed = false; // Resetear flag después de leer
    interrupts();
    return changed;
}

bool encoder_isTurning(void)
{
    // Verifica si ha habido cambio en la última lectura
    return encoder_hasChanged();
}

// Funciones para el pulsador
bool encoder_switch_isPressed(void)
{
    return encoderSwitch.pressed;
}

bool encoder_switch_isClicked(void)
{
    bool clicked = encoderSwitch.clicked;
    encoderSwitch.clicked = false; // Resetear flag después de leer
    return clicked;
}

bool encoder_switch_isHeld(void)
{
    static unsigned long pressStartTime = 0;
    static bool wasPressed = false;

    if (encoderSwitch.pressed && !wasPressed)
    {
        // Acaba de presionarse
        pressStartTime = millis();
    }

    wasPressed = encoderSwitch.pressed;

    // Retorna true si está presionado por más de HOLD_TIME_MS
    return (encoderSwitch.pressed &&
            (millis() - pressStartTime) > HOLD_TIME_MS);
}
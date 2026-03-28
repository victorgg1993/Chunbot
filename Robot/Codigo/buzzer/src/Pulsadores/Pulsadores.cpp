#include <Arduino.h>
#include "Pulsadores.h"

// Variables estáticas para gestión de pulsadores
static pulsadores_state_t buttons = {
    .up = {false, false, 0},
    .down = {false, false, 0},
    .left = {false, false, 0},
    .right = {false, false, 0},
    .ok = {false, false, 0}};

// Array para facilitar el acceso por índice
static const uint8_t buttonPins[] = {
    PULSADOR_FISICO_UP,
    PULSADOR_FISICO_DOWN,
    PULSADOR_FISICO_LEFT,
    PULSADOR_FISICO_RIGHT,
    PULSADOR_FISICO_OK};

static const uint8_t NUM_BUTTONS = 5;

// Función auxiliar para obtener el estado de un pulsador por pin
static button_state_t *getButtonState(uint8_t pin)
{
    switch (pin)
    {
    case PULSADOR_FISICO_UP:
        return &buttons.up;
    case PULSADOR_FISICO_DOWN:
        return &buttons.down;
    case PULSADOR_FISICO_LEFT:
        return &buttons.left;
    case PULSADOR_FISICO_RIGHT:
        return &buttons.right;
    case PULSADOR_FISICO_OK:
        return &buttons.ok;
    default:
        return nullptr;
    }
}

void pulsadores_init(void)
{
    // Configurar todos los pines como entradas con pull-up
    pinMode(PULSADOR_FISICO_UP, INPUT_PULLUP);
    pinMode(PULSADOR_FISICO_DOWN, INPUT_PULLUP);
    pinMode(PULSADOR_FISICO_LEFT, INPUT_PULLUP);
    pinMode(PULSADOR_FISICO_RIGHT, INPUT_PULLUP);
    pinMode(PULSADOR_FISICO_OK, INPUT_PULLUP);

    // Leer estado inicial para evitar falsos clicks al inicio
    pulsadores_polling();
}

void pulsadores_polling(void)
{
    unsigned long currentTime = millis();

    // Procesar cada pulsador
    for (int i = 0; i < NUM_BUTTONS; i++)
    {
        uint8_t pin = buttonPins[i];
        button_state_t *btn = getButtonState(pin);

        if (btn == nullptr)
            continue;

        // Leer estado actual (LOW = presionado por pull-up)
        bool currentPressed = (digitalRead(pin) == LOW);

        // Gestión de debounce
        if (currentPressed != btn->lastState)
        {
            btn->lastDebounceTime = currentTime;
        }

        if ((currentTime - btn->lastDebounceTime) > BUTTON_DEBOUNCE_DELAY)
        {
            if (currentPressed != btn->pressed)
            {
                btn->pressed = currentPressed;
            }
        }

        // Guardar último estado para próxima iteración
        btn->lastState = currentPressed;
    }
}

bool button_isPressed(uint8_t buttonPin)
{
    button_state_t *btn = getButtonState(buttonPin);
    if (btn == nullptr)
        return false;
    return btn->pressed;
}

bool button_isClicked(uint8_t buttonPin)
{
    // Para detectar click, necesitamos mantener un estado estático por cada botón
    static bool wasPressed[5] = {false};
    static uint8_t buttonIndex[5] = {0};

    // Encontrar el índice del botón
    int idx = -1;
    for (int i = 0; i < NUM_BUTTONS; i++)
    {
        if (buttonPins[i] == buttonPin)
        {
            idx = i;
            break;
        }
    }

    if (idx == -1)
        return false;

    button_state_t *btn = getButtonState(buttonPin);
    if (btn == nullptr)
        return false;

    bool currentPressed = btn->pressed;
    bool clicked = false;

    // Detectar cuando se suelta el pulsador (transición de presionado a liberado)
    if (wasPressed[idx] == true && currentPressed == false)
    {
        clicked = true;
    }

    wasPressed[idx] = currentPressed;
    return clicked;
}

bool button_isReleased(uint8_t buttonPin)
{
    button_state_t *btn = getButtonState(buttonPin);
    if (btn == nullptr)
        return false;
    return !btn->pressed;
}

// ========== Funciones específicas para cada pulsador ==========

bool isUpPressed(void)
{
    return button_isPressed(PULSADOR_FISICO_UP);
}

bool isUpClicked(void)
{
    return button_isClicked(PULSADOR_FISICO_UP);
}

bool isDownPressed(void)
{
    return button_isPressed(PULSADOR_FISICO_DOWN);
}

bool isDownClicked(void)
{
    return button_isClicked(PULSADOR_FISICO_DOWN);
}

bool isLeftPressed(void)
{
    return button_isPressed(PULSADOR_FISICO_LEFT);
}

bool isLeftClicked(void)
{
    return button_isClicked(PULSADOR_FISICO_LEFT);
}

bool isRightPressed(void)
{
    return button_isPressed(PULSADOR_FISICO_RIGHT);
}

bool isRightClicked(void)
{
    return button_isClicked(PULSADOR_FISICO_RIGHT);
}

bool isCenterPressed(void)
{
    return button_isPressed(PULSADOR_FISICO_OK);
}

bool isCenterClicked(void)
{
    return button_isClicked(PULSADOR_FISICO_OK);
}

// ========== Funciones auxiliares ==========

uint8_t getAnyButtonPressed(void)
{
    for (int i = 0; i < NUM_BUTTONS; i++)
    {
        if (button_isPressed(buttonPins[i]))
        {
            return buttonPins[i];
        }
    }
    return 0; // Ningún botón presionado
}

uint8_t getAnyButtonClicked(void)
{
    for (int i = 0; i < NUM_BUTTONS; i++)
    {
        if (button_isClicked(buttonPins[i]))
        {
            return buttonPins[i];
        }
    }
    return 0; // Ningún botón clickeado
}
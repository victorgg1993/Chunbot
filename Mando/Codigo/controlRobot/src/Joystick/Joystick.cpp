#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_ADS1X15.h>

#include "Joystick.h"
#include "../Radio/Radio.h"

Adafruit_ADS1115 ads;

// Variables estáticas para gestión de pulsadores
static joystick_buttons_t buttons = {
    .leftButtonPressed = false,
    .rightButtonPressed = false,
    .leftButtonLastState = false,
    .rightButtonLastState = false,
    .lastDebounceTimeLeft = 0,
    .lastDebounceTimeRight = 0
    //
};

void joystick_init(void)
{
    ads.begin();

    // Configurar pines de los pulsadores como entradas con pull-up
    pinMode(JOYSTICK_BUTTON_LEFT, INPUT_PULLUP);
    pinMode(JOYSTICK_BUTTON_RIGHT, INPUT_PULLUP);
}

void joystick_polling()
{
    // Leer valores analógicos del joystick
    int16_t adc1 = ads.readADC_SingleEnded(1);
    int16_t adc2 = ads.readADC_SingleEnded(2);

    uint16_t joystickLY = mapearJoystick(adc1);
    uint16_t joystickRY = mapearJoystick(adc2);

    nrf_send_joystick_izqY(joystickLY);
    nrf_send_joystick_derY(joystickRY);

    // Actualizar estado de pulsadores
    joystick_updateButtons();

    // Enviar estados de pulsadores por RF
    nrf_send_switch(JOYSTICK_BUTTON_LEFT, buttons.leftButtonPressed);
    nrf_send_switch(JOYSTICK_BUTTON_RIGHT, buttons.rightButtonPressed);
}

uint16_t mapearJoystick(int16_t valor)
{
    static const int16_t CENTRO_IDEAL = 11870;
    static const int16_t ZONA_MUERTA = 600;
    static const int16_t MIN_CRUDO = 0;
    static const int16_t MAX_CRUDO = 23500;

    int16_t centroMin = CENTRO_IDEAL - ZONA_MUERTA;
    int16_t centroMax = CENTRO_IDEAL + ZONA_MUERTA;

    // Zona muerta - devolvemos el centro exacto (1000)
    if (valor >= centroMin && valor <= centroMax)
    {
        return 1000; // Centro en 1000
    }

    // Zona inferior (abajo) - mapear a [0, 999]
    if (valor < centroMin)
    {
        if (valor < MIN_CRUDO)
            valor = MIN_CRUDO;
        return map(valor, MIN_CRUDO, centroMin, 0, 999);
    }

    // Zona superior (arriba) - mapear a [1001, 2000]
    if (valor > centroMax)
    {
        if (valor > MAX_CRUDO)
            valor = MAX_CRUDO;
        return map(valor, centroMax, MAX_CRUDO, 1001, 2000);
    }

    return 1000; // Por si acaso
}

void joystick_updateButtons(void)
{
    unsigned long currentTime = millis();

    // Leer estados actuales de los pulsadores (LOW = presionado por pull-up)
    bool currentLeft = (digitalRead(JOYSTICK_BUTTON_LEFT) == LOW);
    bool currentRight = (digitalRead(JOYSTICK_BUTTON_RIGHT) == LOW);

    // Gestión de debounce para pulsador izquierdo
    if (currentLeft != buttons.leftButtonLastState)
    {
        buttons.lastDebounceTimeLeft = currentTime;
    }

    if ((currentTime - buttons.lastDebounceTimeLeft) > DEBOUNCE_DELAY)
    {
        if (currentLeft != buttons.leftButtonPressed)
        {
            buttons.leftButtonPressed = currentLeft;
        }
    }

    // Gestión de debounce para pulsador derecho
    if (currentRight != buttons.rightButtonLastState)
    {
        buttons.lastDebounceTimeRight = currentTime;
    }

    if ((currentTime - buttons.lastDebounceTimeRight) > DEBOUNCE_DELAY)
    {
        if (currentRight != buttons.rightButtonPressed)
        {
            buttons.rightButtonPressed = currentRight;
        }
    }

    // Guardar últimos estados
    buttons.leftButtonLastState = currentLeft;
    buttons.rightButtonLastState = currentRight;
}

bool joystick_isLeftClicked(void)
{
    static bool wasPressed = false;
    bool currentPressed = buttons.leftButtonPressed;
    bool clicked = false;

    // Detectar cuando se suelta el pulsador (transición de presionado a liberado)
    if (wasPressed == true && currentPressed == false)
    {
        clicked = true;
    }

    wasPressed = currentPressed;
    return clicked;
}

bool joystick_isRightClicked(void)
{
    static bool wasPressed = false;
    bool currentPressed = buttons.rightButtonPressed;
    bool clicked = false;

    // Detectar cuando se suelta el pulsador (transición de presionado a liberado)
    if (wasPressed == true && currentPressed == false)
    {
        clicked = true;
    }

    wasPressed = currentPressed;
    return clicked;
}

// Función adicional: detectar si se está manteniendo presionado (útil para acciones continuas)
bool joystick_isLeftPressed(void)
{
    return buttons.leftButtonPressed;
}

bool joystick_isRightPressed(void)
{
    return buttons.rightButtonPressed;
}
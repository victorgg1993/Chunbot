#include <Arduino.h>
#include "Switches.h"

#include "../Radio/Radio.h"

// Estados actuales
bool valor_switch_izquierdo = false;
bool valor_switch_derecho = false;

// Estados anteriores (para detección de cambio)
bool valor_anterior_switch_izquierdo = false;
bool valor_anterior_switch_derecho = false;

// Estados estables (después de antirrebote)
bool estable_switch_izquierdo = false;
bool estable_switch_derecho = false;

// Para antirrebote
unsigned long ultimo_rebote_izq = 0;
unsigned long ultimo_rebote_der = 0;
bool lectura_anterior_izq = false;
bool lectura_anterior_der = false;
const unsigned long TIEMPO_REBOTE = 50; // ms

// Flancos detectados
bool flanco_subida_izq = false;
bool flanco_bajada_izq = false;
bool flanco_subida_der = false;
bool flanco_bajada_der = false;

void switches_init(void)
{
    pinMode(PIN_SWITCH_IZQUIERDO, INPUT_PULLUP);
    pinMode(PIN_SWITCH_DERECHO, INPUT_PULLUP);

    // Lectura inicial
    bool lectura_izq = digitalRead(PIN_SWITCH_IZQUIERDO);
    bool lectura_der = digitalRead(PIN_SWITCH_DERECHO);

    estable_switch_izquierdo = lectura_izq;
    estable_switch_derecho = lectura_der;

    valor_switch_izquierdo = lectura_izq;
    valor_switch_derecho = lectura_der;

    valor_anterior_switch_izquierdo = lectura_izq;
    valor_anterior_switch_derecho = lectura_der;

    lectura_anterior_izq = lectura_izq;
    lectura_anterior_der = lectura_der;

    nrf_send_switch(POS_SWL, valor_switch_izquierdo);
    nrf_send_switch(POS_SWR, valor_switch_derecho);
}

void switches_polling(void)
{
    _switch_readAll();

    if (switch_izquierdo_cambio())
    {
        nrf_send_switch(POS_SWL, valor_switch_izquierdo);
    }

    if (switch_derecho_cambio())
    {
        nrf_send_switch(POS_SWR, valor_switch_derecho);
    }
}

// Detectar cualquier cambio (mantenido por compatibilidad)
bool switch_izquierdo_cambio(void)
{
    if (valor_switch_izquierdo != valor_anterior_switch_izquierdo)
    {
        valor_anterior_switch_izquierdo = valor_switch_izquierdo;
        return true;
    }
    return false;
}

bool switch_derecho_cambio(void)
{
    if (valor_switch_derecho != valor_anterior_switch_derecho)
    {
        valor_anterior_switch_derecho = valor_switch_derecho;
        return true;
    }
    return false;
}

// Nuevas funciones para detectar flancos específicos
bool switch_izquierdo_activado(void)
{
    if (flanco_subida_izq)
    {
        flanco_subida_izq = false; // Limpiar después de leer
        return true;
    }
    return false;
}

bool switch_izquierdo_desactivado(void)
{
    if (flanco_bajada_izq)
    {
        flanco_bajada_izq = false; // Limpiar después de leer
        return true;
    }
    return false;
}

bool switch_derecho_activado(void)
{
    if (flanco_subida_der)
    {
        flanco_subida_der = false;
        return true;
    }
    return false;
}

bool switch_derecho_desactivado(void)
{
    if (flanco_bajada_der)
    {
        flanco_bajada_der = false;
        return true;
    }
    return false;
}

void _switch_readAll(void)
{
    unsigned long ahora = millis();
    _switch_readIzq(ahora);
    _switch_readDer(ahora);
}

void _switch_readIzq(unsigned long ahora)
{
    bool lectura_izq = digitalRead(PIN_SWITCH_IZQUIERDO);

    // Si cambió, reiniciamos temporizador
    if (lectura_izq != lectura_anterior_izq)
    {
        ultimo_rebote_izq = ahora;
        lectura_anterior_izq = lectura_izq;
    }

    // Si pasó el tiempo de rebote y el estado es diferente al estable
    if ((ahora - ultimo_rebote_izq) > TIEMPO_REBOTE)
    {
        if (lectura_izq != estable_switch_izquierdo)
        {

            // Detectar flancos
            if (lectura_izq == HIGH && estable_switch_izquierdo == LOW)
            {
                flanco_subida_izq = true; // LOW → HIGH (activado)
                flanco_bajada_izq = false;
            }
            else if (lectura_izq == LOW && estable_switch_izquierdo == HIGH)
            {
                flanco_bajada_izq = true; // HIGH → LOW (desactivado)
                flanco_subida_izq = false;
            }

            // Actualizar estado estable
            estable_switch_izquierdo = lectura_izq;
            valor_switch_izquierdo = lectura_izq;
        }
    }
}

void _switch_readDer(unsigned long ahora)
{
    bool lectura_der = digitalRead(PIN_SWITCH_DERECHO);

    if (lectura_der != lectura_anterior_der)
    {
        ultimo_rebote_der = ahora;
        lectura_anterior_der = lectura_der;
    }

    if ((ahora - ultimo_rebote_der) > TIEMPO_REBOTE)
    {
        if (lectura_der != estable_switch_derecho)
        {

            if (lectura_der == HIGH && estable_switch_derecho == LOW)
            {
                flanco_subida_der = true;
                flanco_bajada_der = false;
            }
            else if (lectura_der == LOW && estable_switch_derecho == HIGH)
            {
                flanco_bajada_der = true;
                flanco_subida_der = false;
            }

            estable_switch_derecho = lectura_der;
            valor_switch_derecho = lectura_der;
        }
    }
}
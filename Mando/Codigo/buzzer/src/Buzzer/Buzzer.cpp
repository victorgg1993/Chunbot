// Buzzer.cpp - Versión con duraciones corregidas
#include <Arduino.h>
#include <avr/interrupt.h>
#include "Buzzer.h"
#include "notas.h"

// Variables para la generación de tono
static volatile bool tone_active = false;
static volatile unsigned long tone_end_time = 0;
static volatile uint16_t tone_ocr_value = 0;

// Variables para la máquina de estados
static buzzer_estado_t buzzer_estado = BUZZER_IDLE;
static const nota_melodia_t *melodia_actual = nullptr;
static uint16_t melodia_longitud = 0;
static uint16_t nota_actual = 0;
static bool melodia_repetir = false;
static unsigned long tiempo_inicio_nota = 0;

// Variable para controlar si el tono debe detenerse por tiempo
static bool tone_has_duration = false;

// Melodías predefinidas
static const nota_melodia_t startup_melodia[] = {
    {NOTA_C4, 100},
    {NOTA_E4, 100},
    {NOTA_G4, 100},
    {NOTA_C5, 200}};

static const nota_melodia_t error_melodia[] = {
    {NOTA_C4, 200},
    {0, 100},
    {NOTA_C4, 200}};

static const nota_melodia_t success_melodia[] = {
    {NOTA_C4, 100},   // 100ms
    {NOTA_E4, 100},   // 100ms
    {NOTA_G4, 200}};  // 200ms

// Interrupción del Timer1 - Toggle del pin
ISR(TIMER1_COMPA_vect)
{
    if (tone_active)
    {
        digitalWrite(PIN_BUZZER, !digitalRead(PIN_BUZZER));
    }
}

void buzzer_tone(uint16_t frecuencia, uint16_t duracion)
{
    if (frecuencia == 0)
    {
        buzzer_noTone();
        return;
    }

    // Detener tono anterior
    buzzer_noTone();

    // Configurar pin
    pinMode(PIN_BUZZER, OUTPUT);
    digitalWrite(PIN_BUZZER, LOW);

    // Calcular el valor para OCR1A
    unsigned long ocr_value = 16000000UL / (2UL * frecuencia);

    // Verificar que el valor está dentro del rango
    if (ocr_value > 0 && ocr_value <= 65535)
    {
        tone_ocr_value = (uint16_t)ocr_value;

        // Deshabilitar interrupciones mientras configuramos
        noInterrupts();

        // Configurar Timer1 en modo CTC
        TCCR1A = 0;
        TCCR1B = 0;
        TCNT1 = 0;
        OCR1A = tone_ocr_value;
        TCCR1B = (1 << WGM12) | (1 << CS10);  // CTC, prescaler 1
        TIMSK1 |= (1 << OCIE1A);               // Habilitar interrupción

        tone_active = true;
        
        // Guardar la duración si se especificó
        if (duracion > 0)
        {
            tone_end_time = millis() + duracion;
            tone_has_duration = true;
        }
        else
        {
            tone_end_time = 0;
            tone_has_duration = false;
        }

        interrupts();
    }
}

void buzzer_noTone(void)
{
    noInterrupts();

    // Deshabilitar interrupción de Timer1
    TIMSK1 &= ~(1 << OCIE1A);
    
    // Apagar Timer1
    TCCR1A = 0;
    TCCR1B = 0;

    tone_active = false;
    tone_end_time = 0;
    tone_has_duration = false;

    // Apagar el pin
    digitalWrite(PIN_BUZZER, LOW);

    interrupts();
}

void buzzer_init(void)
{
    pinMode(PIN_BUZZER, OUTPUT);
    digitalWrite(PIN_BUZZER, LOW);

    // Inicializar Timer1
    TCCR1A = 0;
    TCCR1B = 0;
    TIMSK1 = 0;

    buzzer_noTone();
    buzzer_estado = BUZZER_IDLE;
    melodia_actual = nullptr;
}

void buzzer_polling(void)
{
    // CRÍTICO: Verificar si el tono actual debe terminar por duración
    if (tone_active && tone_has_duration && tone_end_time > 0)
    {
        if (millis() >= tone_end_time)
        {
            buzzer_noTone();  // Detener el tono cuando se acaba el tiempo
        }
    }

    // Solo procesar si estamos reproduciendo una melodía
    if (buzzer_estado != BUZZER_PLAYING)
    {
        return;
    }

    if (melodia_actual == nullptr)
    {
        buzzer_stop_melodia();
        return;
    }

    unsigned long tiempo_actual = millis();

    // Iniciar nueva nota
    if (tiempo_inicio_nota == 0)
    {
        // Verificar si hemos terminado todas las notas
        if (nota_actual >= melodia_longitud)
        {
            if (melodia_repetir)
            {
                nota_actual = 0;
            }
            else
            {
                buzzer_stop_melodia();
                return;
            }
        }

        const nota_melodia_t &nota = melodia_actual[nota_actual];

        // Reproducir nota o silencio
        if (nota.frecuencia > 0)
        {
            // IMPORTANTE: Pasar la duración para que se detenga automáticamente
            buzzer_tone(nota.frecuencia, nota.duracion);
        }
        else
        {
            buzzer_off();
        }

        // Guardar tiempo de inicio de la nota
        tiempo_inicio_nota = tiempo_actual;
        return;
    }

    // Verificar si la nota actual ha terminado su duración
    const nota_melodia_t &nota_actual_struct = melodia_actual[nota_actual];
    if ((tiempo_actual - tiempo_inicio_nota) >= nota_actual_struct.duracion)
    {
        // Pasar a la siguiente nota
        nota_actual++;
        tiempo_inicio_nota = 0;  // Forzar inicio de nueva nota
        
        // Asegurar que el tono actual se detiene
        if (tone_active)
        {
            buzzer_noTone();
        }
    }
}

void buzzer_off(void)
{
    buzzer_noTone();
}

void buzzer_play(uint16_t nota, uint16_t duracion)
{
    if (buzzer_estado != BUZZER_IDLE)
    {
        buzzer_stop_melodia();
    }

    if (nota > 0)
    {
        buzzer_tone(nota, duracion);
        delay(duracion);  // Esto es bloqueante pero para uso simple
        buzzer_off();
    }
    else
    {
        delay(duracion);
    }
}

void buzzer_play_melodia(const nota_melodia_t *melodia, uint16_t longitud, bool repetir)
{
    // Detener melodía actual si existe
    if (buzzer_estado != BUZZER_IDLE)
    {
        buzzer_stop_melodia();
    }

    if (melodia == nullptr || longitud == 0)
    {
        return;
    }

    // Iniciar nueva melodía
    melodia_actual = melodia;
    melodia_longitud = longitud;
    melodia_repetir = repetir;
    nota_actual = 0;
    tiempo_inicio_nota = 0;
    buzzer_estado = BUZZER_PLAYING;
}

void buzzer_stop_melodia(void)
{
    if (buzzer_estado != BUZZER_IDLE)
    {
        buzzer_off();
        buzzer_estado = BUZZER_IDLE;
        melodia_actual = nullptr;
        nota_actual = 0;
        melodia_longitud = 0;
        melodia_repetir = false;
        tiempo_inicio_nota = 0;
    }
}

void buzzer_pause_melodia(void)
{
    if (buzzer_estado == BUZZER_PLAYING)
    {
        buzzer_off();
        buzzer_estado = BUZZER_PAUSED;
    }
}

void buzzer_resume_melodia(void)
{
    if (buzzer_estado == BUZZER_PAUSED && melodia_actual != nullptr)
    {
        buzzer_estado = BUZZER_PLAYING;
        tiempo_inicio_nota = 0;
    }
}

bool buzzer_is_playing(void)
{
    return (buzzer_estado == BUZZER_PLAYING);
}

void buzzer_beep(uint16_t duracion)
{
    buzzer_play(NOTA_C5, duracion);
}

void buzzer_play_startup(void)
{
    buzzer_play_melodia(startup_melodia,
                        sizeof(startup_melodia) / sizeof(nota_melodia_t),
                        false);
}

void buzzer_play_error(void)
{
    buzzer_play_melodia(error_melodia,
                        sizeof(error_melodia) / sizeof(nota_melodia_t),
                        false);
}

void buzzer_play_success(void)
{
    buzzer_play_melodia(success_melodia,
                        sizeof(success_melodia) / sizeof(nota_melodia_t),
                        false);
}
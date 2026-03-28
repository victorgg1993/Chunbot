// Buzzer.h
#ifndef __BUZZER_H__
#define __BUZZER_H__

#include <Arduino.h>

#define PIN_BUZZER 5

// Estructura para las notas
typedef struct
{
    uint16_t frecuencia;
    uint16_t duracion;
} nota_melodia_t;

typedef enum
{
    BUZZER_IDLE,
    BUZZER_PLAYING,
    BUZZER_PAUSED
} buzzer_estado_t;

// Funciones principales
void buzzer_init(void);
void buzzer_off(void);
void buzzer_play(uint16_t nota, uint16_t duracion);

// Funciones para melodías
template <size_t N>
void buzzer_play_melodia(const nota_melodia_t (&melodia)[N], bool repetir = false)
{
    buzzer_play_melodia(melodia, N, repetir);
}

void buzzer_play_melodia(const nota_melodia_t *melodia, uint16_t longitud, bool repetir = false);
void buzzer_stop_melodia(void);
void buzzer_pause_melodia(void);
void buzzer_resume_melodia(void);
bool buzzer_is_playing(void);
void buzzer_polling(void);

// Funciones de utilidad
void buzzer_beep(uint16_t duracion = 100);
void buzzer_play_startup(void);
void buzzer_play_error(void);
void buzzer_play_success(void);

// Funciones para tono en A0 con Timer1
void buzzer_tone(uint16_t frecuencia, uint16_t duracion = 0);
void buzzer_noTone(void);

#endif
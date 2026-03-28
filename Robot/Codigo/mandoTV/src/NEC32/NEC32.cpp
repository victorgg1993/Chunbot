#include "NEC32.h"

// Estados del decodificador
enum
{
    NEC_IDLE,
    NEC_LEAD_SPACE,
    NEC_DATA
};

// Variables
static uint32_t nec_code = 0;
static uint8_t bit_index = 0;
static bool new_code = false;
static uint8_t state = NEC_IDLE;

static unsigned long lastTime = 0;
static int lastLevel = HIGH;
static unsigned long debug_last_time = 0;

// Temporizaciones NEC (µs)
#define NEC_LEAD_PULSE_MIN 8000
#define NEC_LEAD_PULSE_MAX 10000
#define NEC_LEAD_SPACE_MIN 4000
#define NEC_LEAD_SPACE_MAX 5000
#define NEC_REPEAT_SPACE_MIN 2000
#define NEC_REPEAT_SPACE_MAX 3000
#define NEC_BIT_MARK_MIN 400
#define NEC_BIT_MARK_MAX 800
#define NEC_ZERO_MIN 300
#define NEC_ZERO_MAX 900
#define NEC_ONE_MIN 1200
#define NEC_ONE_MAX 2200

// ---------------------------------------------------------
// Inicialización
// ---------------------------------------------------------
void NEC32_init()
{
    pinMode(NEC32_PIN, INPUT);
    state = NEC_IDLE;
    new_code = false;
    nec_code = 0;
    bit_index = 0;
    lastTime = micros();
    lastLevel = digitalRead(NEC32_PIN);
}

// ---------------------------------------------------------
// Polling: debe llamarse rápido en loop
// ---------------------------------------------------------
void NEC32_update()
{
    int level = digitalRead(NEC32_PIN);
    unsigned long now = micros();

    if (level != lastLevel)
    {
        unsigned long duration = now - lastTime;
        debug_last_time = duration;
        lastTime = now;

        if (level == HIGH)
        { // Flanco LOW->HIGH
            if (state == NEC_IDLE)
            {
                if (duration >= NEC_LEAD_PULSE_MIN && duration <= NEC_LEAD_PULSE_MAX)
                {
                    state = NEC_LEAD_SPACE;
                }
            }
            else if (state == NEC_DATA)
            {
                if (duration < NEC_BIT_MARK_MIN || duration > NEC_BIT_MARK_MAX)
                {
                    state = NEC_IDLE;
                    bit_index = 0;
                }
            }
        }
        else
        { // Flanco HIGH->LOW
            switch (state)
            {
            case NEC_LEAD_SPACE:
                if (duration >= NEC_LEAD_SPACE_MIN && duration <= NEC_LEAD_SPACE_MAX)
                {
                    nec_code = 0;
                    bit_index = 0;
                    state = NEC_DATA;
                }
                else if (duration >= NEC_REPEAT_SPACE_MIN && duration <= NEC_REPEAT_SPACE_MAX)
                {
                    new_code = true;
                    state = NEC_IDLE;
                }
                else
                {
                    state = NEC_IDLE;
                }
                break;
            case NEC_DATA:
                if (duration >= NEC_ZERO_MIN && duration <= NEC_ZERO_MAX)
                {
                    nec_code = (nec_code << 1) | 0;
                    bit_index++;
                }
                else if (duration >= NEC_ONE_MIN && duration <= NEC_ONE_MAX)
                {
                    nec_code = (nec_code << 1) | 1;
                    bit_index++;
                }
                else
                {
                    state = NEC_IDLE;
                    bit_index = 0;
                    break;
                }

                if (bit_index >= 32)
                {
                    new_code = true;
                    state = NEC_IDLE;
                }
                break;
            }
        }

        lastLevel = level;
    }
}

// ---------------------------------------------------------
// Polling helpers
// ---------------------------------------------------------
bool NEC32_isNew()
{
    return new_code;
}

uint32_t NEC32_read()
{
    new_code = false;
    return nec_code;
}

// ---------------------------------------------------------
// Depuración
// ---------------------------------------------------------
void NEC32_debug()
{
    static const char *names[] = {"IDLE", "LEAD_SPACE", "DATA"};
    Serial.print("STATE=");
    Serial.print(names[state]);
    Serial.print(" | bits=");
    Serial.print(bit_index);
    Serial.print(" | code=0x");
    Serial.print(nec_code, HEX);
    Serial.print(" | new=");
    Serial.print(new_code ? "YES" : "NO");
    Serial.print(" | lastΔt=");
    Serial.print(debug_last_time);
    Serial.println(" us");
}

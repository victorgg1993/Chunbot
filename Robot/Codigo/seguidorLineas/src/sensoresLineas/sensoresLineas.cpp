#include "sensoresLineas.h"

// Estructura interna para cada sensor
typedef struct
{
    uint8_t pin;
    bool state;
    bool lastReading;
    unsigned long lastDebounceTime;
} sensor_t;

// Sensores
static sensor_t sensorCentralL = {SENSOR_CENTRAL_L_PIN, false, true, 0};
static sensor_t sensorCentralR = {SENSOR_CENTRAL_R_PIN, false, true, 0};
static sensor_t sensorDer = {SENSOR_DER_PIN, false, true, 0};
static sensor_t sensorIzq = {SENSOR_IZQ_PIN, false, true, 0};

void sensoresLinias_init(void)
{
    pinMode(SENSOR_CENTRAL_L_PIN, INPUT_PULLUP);
    pinMode(SENSOR_CENTRAL_R_PIN, INPUT_PULLUP);
    pinMode(SENSOR_DER_PIN, INPUT_PULLUP);
    pinMode(SENSOR_IZQ_PIN, INPUT_PULLUP);
    sensoresLinias_polling();
}

static void updateSensor(sensor_t *s)
{
    bool reading = digitalRead(s->pin);

    if (reading != s->lastReading)
    {
        s->lastDebounceTime = millis();
    }

    if ((millis() - s->lastDebounceTime) > SENSORES_DEBOUNCE_MS)
    {
        // Sensor activo en LOW (pull-up)
        s->state = (reading == LOW);
    }

    s->lastReading = reading;
}

void sensoresLinias_polling(void)
{
    updateSensor(&sensorCentralL);
    updateSensor(&sensorCentralR);
    updateSensor(&sensorDer);
    updateSensor(&sensorIzq);
}

// Lecturas ( van invertidas )
bool sensorCentralL_isActive(void)
{
    return !sensorCentralL.state;
}

bool sensorCentralR_isActive(void)
{
    return !sensorCentralR.state;
}

bool sensor_der_isActive(void)
{
    return !sensorDer.state;
}

bool sensor_izq_isActive(void)
{
    return !sensorIzq.state;
}
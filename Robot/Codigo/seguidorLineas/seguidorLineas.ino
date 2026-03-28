// plaquita: Arduino mega 2560

#include "src/Motores/Motores.h"
#include "src/sensoresLineas/sensoresLineas.h"

int8_t direccion_robot = 0; // -1 derecha, 0 recto, 1 izquierda

#define RECTO 0
#define DERECHA 1
#define IZQUIERDA 2

bool centrado = true;
uint8_t sentido = RECTO;

void setup()
{
  Serial.begin(9600);

  motores_init();
  sensoresLinias_init();

  delay(100);
  sensoresLinias_polling();

  adelante();
  // Serial.println("adelante");
}

void loop()
{
  sensoresLinias_polling();

  // -------------------------------- sensores interiores
  if (sensorCentralL_isActive() || sensorCentralR_isActive())
  {
    centrado = true;
  }

  // -------------------------------- sensores exteriores
  if (sensor_izq_isActive())
  {
    sentido = DERECHA;
    centrado = false;
    izquierda();
  }

  if (sensor_der_isActive())
  {
    sentido = IZQUIERDA;
    centrado = false;
    derecha();
  }

  // -------------------------------- extra ( cuando se logró centrar al robot )
  if (centrado)
  {
    switch (sentido)
    {
    case IZQUIERDA:
      if (sensorCentralL_isActive())
      {
        sentido = DERECHA;
        izquierda();
      }
      break;

    case DERECHA:
      if (sensorCentralR_isActive())
      {
        sentido = IZQUIERDA;
        derecha();
      }
      break;

    default:
      sentido = RECTO;
      adelante();
      break;
    }
  }
}

// -------------------------------- Sensores

// -------------------------------- Motor
void adelante()
{
  motor_runProporcional(MOTOR_IZQUIERDO, 104);
  motor_runProporcional(MOTOR_DERECHO, 85);
}

void izquierda()
{
  motor_runProporcional(MOTOR_IZQUIERDO, 90);
  motor_runProporcional(MOTOR_DERECHO, 85);
}

void derecha()
{
  motor_runProporcional(MOTOR_IZQUIERDO, 104);
  motor_runProporcional(MOTOR_DERECHO, 90);
}

void detenido()
{
  motor_runProporcional(MOTOR_IZQUIERDO, 90);
  motor_runProporcional(MOTOR_DERECHO, 90);
}
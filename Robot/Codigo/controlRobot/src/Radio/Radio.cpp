#include <Arduino.h>
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

#include "../globals.h"
#include "Radio.h"

RF24 radio(PIN_RADIO_CE, PIN_RADIO_CSN);
const byte address[6] = "9F5FA";

uint8_t receive_buffer[64];
uint8_t buffer_index = 0;

unsigned long lastPacketTime = 0;

void nrf_init(void)
{
    if (!radio.begin())
    {
        Serial.println("NRF24 NO detectado");
    }

    radio.setChannel(100);
    radio.setDataRate(RF24_2MBPS);
    radio.setPALevel(RF24_PA_LOW);
    radio.setCRCLength(RF24_CRC_16);
    radio.setAutoAck(true);
    radio.setPayloadSize(SIZE_PAQUETE);

    radio.setRetries(5, 15);

    radio.openReadingPipe(1, address);
    radio.startListening();

    Serial.println("Robot radio ok");
}

void nrf_polling(void)
{
    // Timeout de seguridad - si pasa mucho tiempo sin completar paquete, reset
    if (buffer_index > 0 && millis() - lastPacketTime > PACKET_TIMEOUT)
    {
        Serial.println("Packet timeout - reset");
        buffer_index = 0;
    }

    if (radio.available())
    {

        uint8_t temp_buffer[SIZE_PAQUETE];
        radio.read(temp_buffer, sizeof(temp_buffer));

        // Actualizar tiempo del último dato recibido
        lastPacketTime = millis();

        for (int i = 0; i < SIZE_PAQUETE; i++)
        {
            uint8_t byte_recibido = temp_buffer[i];

            // Verificar índice válido
            if (buffer_index >= sizeof(receive_buffer))
            {
                Serial.println("Buffer index overflow - reset");
                buffer_index = 0;
                return;
            }

            if (byte_recibido == 0xFF)
            {
                if (buffer_index > 0 && receive_buffer[buffer_index - 1] == 0xFF)
                {
                    // FIN DE PAQUETE ENCONTRADO
                    if (buffer_index - 1 > 0)
                    {
                        _nrf_procesar_paquete(receive_buffer, buffer_index - 1);
                    }

                    // Reset para siguiente paquete
                    buffer_index = 0;
                    return;
                }
                else
                {
                    // Primer FF - guardar si hay espacio
                    if (buffer_index < sizeof(receive_buffer) - 1)
                    {
                        receive_buffer[buffer_index++] = 0xFF;
                    }
                    else
                    {
                        Serial.println("Buffer full en FF - reset");
                        buffer_index = 0;
                        return;
                    }
                }
            }
            else
            {
                // Byte normal
                if (buffer_index < sizeof(receive_buffer) - 1)
                {
                    receive_buffer[buffer_index++] = byte_recibido;
                }
                else
                {
                    Serial.println("Buffer full en datos - reset");
                    _nrf_hard_reset();
                    buffer_index = 0;
                    return;
                }
            }
        }
    }
}

void _nrf_procesar_paquete(uint8_t *data, uint8_t length)
{
    // ----------------------------------------------------------------------- interruptor izquierdo
    estado_switch_izquierdo = data[POS_SWL] == 0xF ? LOW : HIGH;

    if (estado_switch_izquierdo != estado_switch_izquierdo_anterior)
    {
        estado_switch_izquierdo_anterior = estado_switch_izquierdo;
        cambio_switch_izquierdo = true;
    }

    // ----------------------------------------------------------------------- interruptor derecho
    estado_switch_derecho = data[POS_SWR] == 0xF ? LOW : HIGH;

    if (estado_switch_derecho != estado_switch_derecho_anterior)
    {
        estado_switch_derecho_anterior = estado_switch_derecho;
        cambio_switch_derecho = true;
    }

    // ----------------------------------------------------------------------- joystick izquierdo
    valor_joystick_izquierdoY = data[POS_JOYLYL] | (data[POS_JOYLYH] << 8);
    valor_joystick_izquierdoY = _nrf_joystick_izquierdo(valor_joystick_izquierdoY);

    // ----------------------------------------------------------------------- joystick derecho
    valor_joystick_derechoY = data[POS_JOYRYL] | (data[POS_JOYRYH] << 8);
    valor_joystick_derechoY = _nrf_joystick_derecho(valor_joystick_derechoY);

    // Serial.print(valor_joystick_izquierdoY);
    // Serial.print(" - ");
    // Serial.print(valor_joystick_derechoY);
    // Serial.println("");
}

void _nrf_hard_reset(void)
{
    radio.flush_rx();
    radio.flush_tx();

    radio.stopListening();
    delay(10);

    radio.powerDown();
    delay(100);
    radio.powerUp();
    delay(100);

    nrf_init();

    // 7. Resetear variables locales
    buffer_index = 0;
    memset(receive_buffer, 0, BUFFER_SIZE);
}

uint16_t _nrf_joystickAjustar(uint8_t motor, uint16_t valorLeido)
{
    // Por defecto, joystick centro
    uint8_t valorServo = 90;

    // joystick arriba
    if (valorLeido > ZONA_MUERTA_SUP)
    {
        if (motor == MOTOR_IZQUIERDO)
        {
            valorServo = map(valorLeido, 1024, 2000, 91, 180);
        }
        else
        {
            valorServo = map(valorLeido, 1024, 2000, 89, 0);
        }
    }

    // joystick abajo
    else if (valorLeido < ZONA_MUERTA_INF)
    {
        if (motor == MOTOR_IZQUIERDO)
        {
            valorServo = map(valorLeido, 0, 1013, 0, 89);
        }
        else
        {
            valorServo = map(valorLeido, 0, 1013, 180, 91);
        }
    }

    valorLeido = constrain(valorServo, 0, 180);

    return valorLeido;
}

uint16_t _nrf_joystick_izquierdo(uint16_t valorLeido)
{
    uint16_t _valor = _nrf_joystickAjustar(MOTOR_IZQUIERDO, valorLeido);

    if (_valor != valor_joystick_izquierdoY_anterior)
    {
        valor_joystick_izquierdoY_anterior = _valor;
        cambio_joystick_izquierdoY = true;
    }

    return _valor;
}

uint16_t _nrf_joystick_derecho(uint16_t valorLeido)
{
    uint16_t _valor = _nrf_joystickAjustar(MOTOR_DERECHO, valorLeido);

    if (_valor != valor_joystick_derechoY_anterior)
    {
        valor_joystick_derechoY_anterior = _valor;
        cambio_joystick_derechoY = true;
    }

    return _valor;
}
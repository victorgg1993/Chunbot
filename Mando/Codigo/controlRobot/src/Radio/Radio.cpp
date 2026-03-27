#include <Arduino.h>
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <SPI.h>
// #include <printf.h>

#include "Radio.h"

RF24 radio(PIN_RADIO_CE, PIN_RADIO_CSN);

const byte address[6] = "9F5FA";

// El mensaje ha de ser fijo. Ha de coincidir con el robot
// [0,1] joystick izquierdo ( eje Y ) [2,3] joystick derecho ( eje Y ) [4] switch izquierdo [5] switch derecho
// los últimos bytes se usan para sincronizar el paquete
uint8_t message[] = {0, 0, 0, 0, 0, 0, 0xFF, 0xFF};

void nrf_init(void)
{
    // printf_begin();

    if (!radio.begin())
    {
        Serial.println("NRF24 NO detectado");
    }
    else
    {
        radio.setChannel(100);
        radio.setDataRate(RF24_2MBPS);
        radio.setPALevel(RF24_PA_LOW);
        radio.setCRCLength(RF24_CRC_16);
        radio.setAutoAck(true);
        radio.setPayloadSize(32);

        radio.openWritingPipe(address);
        radio.stopListening();
        // radio.printDetails();
    }

    Serial.println("Mando radio ok");
}

void nrf_polling(void)
{
    radio.write(message, sizeof(message)); // enviar només quan hi hagi un canvi
}

void nrf_send_joystick_izqX(uint16_t eje_x) {}

void nrf_send_joystick_izqY(uint16_t eje_y)
{
    // uint16_t reconstruir = (message[2] << 8) | message[1];
    message[POS_JOYLYL] = (eje_y & 0xFF);
    message[POS_JOYLYH] = ((eje_y >> 8) & 0xFF);
}

void nrf_send_joystick_derX(uint16_t eje_x) {}

void nrf_send_joystick_derY(uint16_t eje_y)
{
    message[POS_JOYRYL] = (eje_y & 0xFF);
    message[POS_JOYRYH] = ((eje_y >> 8) & 0xFF);
}

void nrf_send_switch(char lado, bool estado)
{
    if (lado == LADO_L)
    {
        message[POS_SWL] = estado ? 0x0F : 0x00;
    }

    if (lado == LADO_R)
    {
        message[POS_SWR] = estado ? 0x00 : 0x0F; //
    }
}

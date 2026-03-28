# Mando 春 Bot

## Contenido:
- PCB: Diseño de la PCB, tanto esquemáticos como la propia PCB ( Kicad )
- 3D: Modelos 3D ( FreeCAD )
- Codigo: Contiene códigos de ejemplo ( Arduino Nano )

## Pines:


|     Uso       |  Pin  |                                Uso                                    |
|    :---:      | :---: |                               :---:                                   |
| Interruptores |  D5   | Interruptor lateral derecho                                           |
| Interruptores |  D6   | Interruptor lateral izquierdo                                         |
|               |       |                                                                       |
| Encoder       |  D2   | Encoder, pin A. Usa interrupciones                                    |
| Encoder       |  D3   | Encoder, pin B. Usa interrupciones                                    |
| Encoder       |  D4   | Pulsador del encoder                                                  |
|               |       |                                                                       |
| Zumbador      |  A0   | Pin PWM para el control del zumbador ( buzzer )                       |
|               |       |                                                                       |
| Joystick      |  A4   | SDA chip ADC ( analogic to digital converter ) usado para el joystick |
| Joystick      |  A5   | SCL chip ADC ( analogic to digital converter ) usado para el joystick |
| Joystick      |  A6   | alert pin del chip ADC ( no implementado )                            |
| Joystick      |  D7   | Pulsador joystick izquierdo                                           |
| Joystick      |  D8   | Pulsador joystick derecho                                             |
|               |       |                                                                       |
|  OLED         |  A4   |  SDA, bus I2C de la pantalla OLED. Pin compartido con el joystick     |
|  OLED         |  A5   |  SCL, bus I2C de la pantalla OLED. Pin compartido con el joystick     |
|               |       |                                                                       |
|   Radio       | D13   |  Módulo radio NRF24L01, pin SPI SCK                                   |
|   Radio       | D12   |  Módulo radio NRF24L01, pin SPI MISO                                  |
|   Radio       | D11   |  Módulo radio NRF24L01, pin SPI MOSI                                  |
|   Radio       | D10   |  Módulo radio NRF24L01, pin SPI #CNS                                  |
|   Radio       | D9    |  Módulo radio NRF24L01, pin SPI CE                                    |
|               |       |                                                                       |

#ifndef _LM35_
#define _LM35_

#include "Luces.h"

#define PIN_LUCES A14

void luces_init(void);
void luces_write(uint8_t status);
void luces_polling(void);

#endif
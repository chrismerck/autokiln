#ifndef __I2C_H__
#define __I2C_H__

#include "hal.h"

void I2C_Init();

int32_t I2C_Transfer(
    I2CDriver * bus,
    uint8_t addr,
    const uint8_t* txbuf, int txbytes, 
    uint8_t* rxbuf, int rxbytes);

// Response Codes
// These are identical to ChibiOS RDY_OK, RDY_TIMEOUT, and RDY_RESET
#define PROJ_I2C_ACK      0
#define PROJ_I2C_TIMEOUT -1
#define PROJ_I2C_NAK     -2

#endif // __I2C_H__

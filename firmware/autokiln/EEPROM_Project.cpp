// Project-specific code for Serial EEPROM
// Copyright (c) 2014 Chris Merck

#include "ch.h"
#include "hal.h"
#include"EEPROM.h"
#define SYS_CURRENT_SUBSYS SYS_SUBSYS_EEPROM
#include"Sys.h"
#include"I2C.h"

EEPROM_24XX512 * g_pEEPROM = NULL;

void CreateEEPROM()
{
  // allocate memory for each device
  g_pEEPROM = new EEPROM_24XX512(0b000);

  // initialize each device
  g_pEEPROM->Init();
}

int32_t EEPROM_24XX512::ProjI2CTransfer(uint8_t addr,
    const uint8_t* txbuf, int txbytes, uint8_t* rxbuf, int rxbytes)
{
 return I2C_Transfer(&I2CD1, addr, txbuf, txbytes, rxbuf, rxbytes);
}


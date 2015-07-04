// Microchip 24XX512 I2C EEPROM_24XX512
// Copyright (c) 2014 Chris Merck

#ifndef __EEPROM_24XX512_H__
#define __EEPROM_24XX512_H__

#include<stdint.h>

class EEPROM_24XX512 
{
public:
  EEPROM_24XX512(uint8_t hw_addr);

  bool Init();

  bool Read(uint8_t * data, uint16_t addr, uint16_t bytes);
  bool Write(const uint8_t * data, uint16_t addr, uint16_t bytes);

private:

  bool WriteRaw(const uint8_t * data, uint16_t addr, uint16_t bytes);

  /*** Project-Specific ***/
  int32_t ProjI2CTransfer(uint8_t addr, 
      const uint8_t* txbuf, int txbytes, uint8_t* rxbuf, int rxbytes);

  /*** Member Data ***/
  uint8_t i2c_addr;
};

#endif //__EEPROM_24XX512_H__


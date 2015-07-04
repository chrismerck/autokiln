// Microchip 24XX512 I2C EEPROM Driver
// Copyright (c) 2014 Chris Merck

#include"EEPROM.h"
#define SYS_CURRENT_SUBSYS SYS_SUBSYS_EEPROM
#include"Sys.h"
#include"I2C.h" // for I2C_OK, etc. defs

/*** PUBLIC ***/

EEPROM_24XX512::EEPROM_24XX512(uint8_t A)
{
  // A = 0b001 means A0 = 1, A1&A2 = 0
  i2c_addr = 0b1010000 | A;

  // we DO NOT actually initalize part here
  // user MUST call Init()
}

bool EEPROM_24XX512::Init()
{
  // reset current address to zero
  bool status;
  if (!(status=WriteRaw(NULL,0x0000,0)))
  {
    SysError("Init failed.");
  }
  return status;
}

/// Write any amount of data to EEPROM,
///  handling 128B page boundries.
bool EEPROM_24XX512::Write(const uint8_t * data, uint16_t addr, uint16_t bytes)
{
  // TODO: handle writing across page boundires.
  // For now we force writes only within single pages.
  if (bytes == 0 || ((addr + (bytes-1))>>7 != addr>>7))
  {
    SysWarning("Paging error.");
    return false;
  }
  return WriteRaw(data,addr,bytes);
}

/// Read any amount of data from EEPROM.
bool EEPROM_24XX512::Read(uint8_t * data, uint16_t addr, uint16_t bytes)
{
  uint8_t txbuf[2];
  txbuf[0] = (addr>>8) & 0x00FF; 
  txbuf[1] = addr & 0x00FF; 
  if (ProjI2CTransfer(i2c_addr,
        txbuf, 2, /* addr */
        data, bytes)!=MSG_OK)
    return false;
  return true;
}


/*** PRIVATE ***/

/// Raw Write, will rollover if you cross a 128B page boundry.
bool EEPROM_24XX512::WriteRaw(const uint8_t * data, uint16_t addr, uint16_t bytes)
{
  int32_t r;
  uint8_t txbuf[2+128];
  txbuf[0] = (addr>>8) & 0x00FF; 
  txbuf[1] = addr & 0x00FF; 
  memcpy(&txbuf[2],data,bytes);
  if (ProjI2CTransfer(i2c_addr,
        txbuf, 2+bytes, /* addr + data */
        NULL, 0)!=MSG_OK)
    return false;

  // wait for write to finish
  int i;
  txbuf[0] = 0x00;
  txbuf[1] = 0x00;
  for (i=0;i<10;i++)
  {
    OsSleepMs(1);
    // EEPROM will only ACK once write is finished
    r = ProjI2CTransfer(i2c_addr,txbuf,2,NULL,0);
    if (r==MSG_TIMEOUT) return false; // some other I2C error
    if (r==MSG_OK) return true;  // finished
  }
  SysError("Write timeout.");
  return false;
}




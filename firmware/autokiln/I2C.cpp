// Project-Specific I2C Implementation
// Copyright (c) 2014 Chris Merck

#include"ch.h"
#include"hal.h"
#define SYS_CURRENT_SUBSYS SYS_SUBSYS_OS 
#include"Sys.h"
#include"I2C.h"

#define I2C_FREQ  100000

static const I2CConfig i2c_cfg = {
  STM32_TIMINGR_PRESC(15U) |
  STM32_TIMINGR_SCLDEL(4U) | STM32_TIMINGR_SDADEL(2U) |
  STM32_TIMINGR_SCLH(15U)  | STM32_TIMINGR_SCLL(21U),
  0,
  0
};

/*** (re)initialize all I2C buses **/
void I2C_Init()
{
  i2cStart(&I2CD1, &i2c_cfg); 
}

/*** transfer data on an I2C bus
 * Performs: write, reset, read 
 * Address is 7-bit (do not add RW bit) ***/
int32_t I2C_Transfer(
    I2CDriver * bus,
    uint8_t addr,
    const uint8_t* txbuf, int txbytes, 
    uint8_t* rxbuf, int rxbytes)
{
  msg_t r;
  //uint8_t dummy_rxbuf[2];
  int timeout_ms = 4/*min timeout*/ + (rxbytes+txbytes+2)*9*1000/I2C_FREQ;
  i2cAcquireBus(bus);
  // always transmit, but use restart condition 
  //  if there are bytes to be read.
#if 0
  SysDebug("I2C_Transfer(addr=0x%02X,txbytes=%d,rxbytes=%d) timeout=%dms",
      addr,txbytes,rxbytes,timeout_ms);
#endif 
  if ((txbuf != NULL) && (txbytes > 0))
  {
    r = i2cMasterTransmitTimeout(bus,
        addr, txbuf, txbytes, rxbuf, rxbytes,
        MS2ST(timeout_ms));
  } 
  else if ((txbuf == NULL) && (txbytes == 0))
  {
    /*if (rxbytes == 1)
    {
      // workaround for STM32F1 bug
      // cannot read single byte, 
      // so read 2 bytes and only return 
      // first byte
      // (But this has the nasty side-effect
      //  of possibly doing something the calling
      //  driver did not intend... so better
      //  to not support reading single byte.)
      r = i2cMasterReceiveTimeout(bus,
          addr, dummy_rxbuf, 2,
          MS2ST(timeout_ms));
      rxbuf[0] = dummy_rxbuf[0];
    }
    else*/
    {
      r = i2cMasterReceiveTimeout(bus,
          addr, rxbuf, rxbytes,
          MS2ST(timeout_ms));
    }
  }
  else
  {
    SysError("I2C_Transfer invalid param.");
    r = MSG_RESET; // emulate NAK
  }
  if (r == MSG_TIMEOUT)
  {
    SysError("I2C Timeout");
    // restart the bus
    i2cStart(bus, &i2c_cfg);
  }
  else if (r == MSG_RESET)
  {
    // a NAK must be handled by the calling driver
  }
  i2cReleaseBus(bus);
  return r;
}


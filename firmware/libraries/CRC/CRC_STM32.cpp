/** STM32 Hardware Accelerated CRC32 Implementation **/

#include"hal.h"
#include"CRC.h"
#include"Os.h"
#define SYS_CURRENT_SUBSYS SYS_SUBSYS_CRC
#include"Sys.h"

static os_lock_t * crc_lock = 0;

static void CRC_Lock()
{
  if (!crc_lock)
  {
    crc_lock = OsCreateLock();
  }
  OsLock(crc_lock);
}

static void CRC_Unlock()
{
  OsUnlock(crc_lock);
}

uint32_t CRC32(const uint8_t * buf, uint32_t len)
{
  uint32_t tmp;

  // for thread-safety
  // Note: 512kB CRC measured at 103ms on STM32F103 @ 8MHz
  CRC_Lock();

  // enable CRC clock
  RCC->AHBENR |= RCC_AHBENR_CRCEN;

  SysInfo("CRC32(buf=0x%08X len=%d)",(uint32_t)buf,len);

  // reset CRC state machine
  CRC->CR |= CRC_CR_RESET;

  // load buffer
  uint32_t i = 0;
  while (i<len)
  {
    if (i+4<len)
    {
      // compute full 4-byte word
      tmp = *((uint32_t*)((void*)&buf[i]));
      SysDebug("  CRC Load Full i=%d tmp=0x%08X DR=0x%08X",i,tmp,CRC->DR);
      CRC->DR = tmp;
      i+=4;
    }
    else
    {
      // load first 1, 2, or 3 bytes of tmp with end of buf
      uint32_t tmp = 0x00000000;
      for (uint32_t j=0;i<len;i++)
      {
        ((uint8_t*)&tmp)[j] = buf[i];
        j++;
      }
      // compute partial word (with trailing zero bytes)
      SysDebug("  CRC Load Partial i=%d tmp=0x%08X DR=0x%08X",i,tmp,CRC->DR);
      CRC->DR = tmp;
    }
  }

  uint32_t crc = CRC->DR;

  // disable CRC clock
  RCC->AHBENR &= ~(RCC_AHBENR_CRCEN);

  SysInfo("CRC32 = 0x%08X",crc);

  CRC_Unlock();

  return crc;
}


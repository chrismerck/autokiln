
#include"Sys.h"

/**
 * Boot-time Default System Debug Levels
 */

void SysSetDebugLevels_Project()
{
  SysSetDebugLevel(SYS_SUBSYS_MAIN,SYS_INFO);
  SysSetDebugLevel(SYS_SUBSYS_WDG,SYS_DEBUG);
  SysSetDebugLevel(SYS_SUBSYS_OS,SYS_INFO);
  SysSetDebugLevel(SYS_SUBSYS_EEPROM,SYS_DEBUG);
  SysSetDebugLevel(SYS_SUBSYS_POWER,SYS_INFO);
  SysSetDebugLevel(SYS_SUBSYS_ADC,SYS_INFO);
  SysSetDebugLevel(SYS_SUBSYS_UART,SYS_DEBUG);
  SysSetDebugLevel(SYS_SUBSYS_FLASH,SYS_INFO);
  SysSetDebugLevel(SYS_SUBSYS_CRC,SYS_WARNING);
  SysSetDebugLevel(SYS_SUBSYS_BOOTCTRL,SYS_DEBUG);
  SysSetDebugLevel(SYS_SUBSYS_DBG,SYS_DEBUG);
}

/**
 * System Command Handler Table
 */



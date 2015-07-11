/*
    GSN-STM32 Main Program
    Copyright (c) 2014 Chris Merck
*/

#include "hal.h"
#include "globals.h"
#include "Os.h"
#define SYS_CURRENT_SUBSYS  SYS_SUBSYS_MAIN
#include "Sys.h"
#include "DbgConsole.h"
#include "string.h"
#include "stdio.h"
#include "EEPROM.h"
#include "I2C.h"
//#include "RTC.h"
#include "ImageInfo.h"
#include "LCD.h"
#include "Input.h"
#include<cstdio>
#include<cstdlib>

/*===========================================================================*/
/* Initialization and main thread.                                           */
/*===========================================================================*/

int32_t click = 0;

/* Triggered when the button is pressed or released. The LED4 is set to ON.*/
void extcb1(EXTDriver *extp, expchannel_t channel) {
  (void)extp;
  (void)channel;
  chSysLockFromISR();
  click++;
  chSysUnlockFromISR();
}

static const EXTConfig extcfg = {
  {
    {EXT_CH_MODE_DISABLED, NULL},
    {EXT_CH_MODE_DISABLED, NULL},
    {EXT_CH_MODE_DISABLED, NULL},
    {EXT_CH_MODE_BOTH_EDGES | EXT_CH_MODE_AUTOSTART | EXT_MODE_GPIOB, extcb1}, // PB3 = ENC_A
    {EXT_CH_MODE_DISABLED, NULL},
    {EXT_CH_MODE_BOTH_EDGES | EXT_CH_MODE_AUTOSTART | EXT_MODE_GPIOB, extcb1}, // PB5 = ENC_B
    {EXT_CH_MODE_DISABLED, NULL},
    {EXT_CH_MODE_DISABLED, NULL},
    {EXT_CH_MODE_DISABLED, NULL},
    {EXT_CH_MODE_DISABLED, NULL},
    {EXT_CH_MODE_DISABLED, NULL},
    {EXT_CH_MODE_DISABLED, NULL},
    {EXT_CH_MODE_DISABLED, NULL},
    {EXT_CH_MODE_DISABLED, NULL},
    {EXT_CH_MODE_DISABLED, NULL},
    {EXT_CH_MODE_DISABLED, NULL},
    {EXT_CH_MODE_DISABLED, NULL},
    {EXT_CH_MODE_DISABLED, NULL},
    {EXT_CH_MODE_DISABLED, NULL},
    {EXT_CH_MODE_DISABLED, NULL},
    {EXT_CH_MODE_DISABLED, NULL},
    {EXT_CH_MODE_DISABLED, NULL},
    {EXT_CH_MODE_DISABLED, NULL}
  }
};



/*
 * Application entry point.
 * Stack size defined in linker.ld (see __process_stack__)
 */
int main(void) {


  /*
   * Real-Time Operating System Initialization
   * - HAL initialization, this also initializes the configured device drivers
   *   and performs the board-specific initializations.
   * - Kernel initialization, the main() function becomes a thread and the
   *   RTOS is active.
   */
  halInit();
  chSysInit();

  /*
   * Activates the EXT driver 1.
   */
  extStart(&EXTD1, &extcfg);

  setPin(PPIN_LCD_BKL_EN);
  OsSleepMs(500);
  clearPin(PPIN_LCD_BKL_EN);
  OsSleepMs(5000);

  SysDefaultDebugLevels();
  SysSetDebugLevels_Project();

  /*
   * Reboot Message
   * TODO: Add firmware version and reboot reason
   */
  DbgConsoleInit(); 
  SysDebugPrintf("\r\n\r\n");
  SysDebugPrintf("*********************************\r\n");
  SysDebugPrintf("*   Autokiln Controller Application\r\n");
  SysDebugPrintf("*   Image: %-20s\r\n",IMAGE_NAME);
  SysDebugPrintf("* Version: %-20s\r\n",IMAGE_VERSION);
  SysDebugPrintf("*  Commit: %08x\r\n",IMAGE_COMMIT);
  SysDebugPrintf("*    Date: %-20s\r\n",IMAGE_DATETIME);
  SysDebugPrintf("*********************************\r\n");

  /*
   * Timer Task Initialization
   */
  OsTimerInit();

  /*
   * LCD Initialization
   */
  LCD_Init();

  /*
   * Microcontroller-Internal 
   * Peripheral Initialization
   */
  SysInfo("Starting I2C...");
  I2C_Init();
  //SysInfo("Starting RTC...");
  //RTC_Init();

  /*
   * Chip Driver Initialization
   */
  SysInfo("Creating Watchdog...");
  CreateWatchdog();
#if 0
  SysInfo("Creating EEPROM...");
  CreateEEPROM();
  SysInfo("Creating Uart...");
  CreateUart();
#endif

  /*
   * Tasks
   */
  Input_Init();

  /*
   * Start Main Application Loop
   */
  SysInfo("System Ready!");

  sprintf((char*)&lcd_buf[LCD_XMAX],  "Wood Kiln Controller");
  sprintf((char*)&lcd_buf[2*LCD_XMAX]," \"Autokiln\"  v0.1 ");
  LCD_Redraw();
  
  int i = 0;
  while(1)
  {
    i++;
    OsSleepMs(1000);
  }
}
 

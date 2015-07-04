/**
 * globals.h - pointers to shared resources
 **/

#ifndef __GLOBALS_H__
#define __GLOBALS_H__

#include"Watchdog.h"
#include"EEPROM.h"

extern Watchdog * g_pWatchdog;
extern void CreateWatchdog();

#endif // __GLOBALS_H__

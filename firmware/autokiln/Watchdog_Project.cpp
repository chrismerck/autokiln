// Project-Specific Watchdog Code
// Copyright (c) 2014 Chris Merck

#include"Watchdog.h"
#include"hal.h"
#include"Os.h"

Watchdog * g_pWatchdog = NULL;

bool CreateWatchdog()
{
  g_pWatchdog = new Watchdog();
  if (!g_pWatchdog) return false;
  g_pWatchdog->Start();
  return true;
}

bool Watchdog::HwPet_Project()
{
  /* todo */
  return true;
}

bool Watchdog::TickHook_Project(bool status)
{
  if (status)
  {
    //setPin(PIN_HEARTBEAT);
    OsSleepMs(100);
    //clearPin(PIN_HEARTBEAT);
    OsSleepMs(100);
  }
  else
  {
    OsSleepMs(200);
  }
  //setPin(PIN_HEARTBEAT);
  OsSleepMs(100);
  //clearPin(PIN_HEARTBEAT);
  OsSleepMs(100);
  return true;
}



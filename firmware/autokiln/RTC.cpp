// Real-Time Clock Driver
// Copyright (c) 2014 Chris Merck

#include"RTC.h"
#define SYS_CURRENT_SUBSYS SYS_SUBSYS_OS
#include"Sys.h"
#include"hal.h"
#include"rtc.h"
#include"Os.h"
#include"Menu.h"

uint32_t rtc_ticks = 0;

static RTCDateTime timespec;
//static RTCAlarm alarmspec;

extern int32_t weight_curr;

static void RTC_Tick_Hook()
{
  rtc_ticks++;
  /* call hooks to update menus etc. */
  g_pCurrentMenu->Redraw();
}

static void RTC_CheckXtal()
{
  if (!(RCC->BDCR & RCC_BDCR_LSERDY))
    SysWarning("RTC XTAL unstable.");
}

uint32_t RTC_GetTime()
{
  RTC_CheckXtal();
  rtcGetTime(&RTCD1, &timespec);
  return timespec.millisecond;
}

static void RTC_Timer(void * arg) {
  (void) arg;
  static uint32_t prev_sec = 0;
  uint32_t now = RTC_GetTime();
  if (now - prev_sec > 1000) {
    prev_sec = now;
    RTC_Tick_Hook();
  }
}

void RTC_Init()
{
  // reset the backup domain
  PWR->CR |= PWR_CR_DBP;
  RCC->BDCR |= RCC_BDCR_BDRST;
  RCC->BDCR &= ~(RCC_BDCR_BDRST);

  rtcGetTime(&RTCD1, &timespec);

  // enable backup and pwr clocks
  //RCC->APB1ENR |= RCC_APB1ENR_BKPEN;
  RCC->APB1ENR |= RCC_APB1ENR_PWREN;

  // enable LSE and wait for it to stabilize
  RCC->BDCR |= RCC_BDCR_LSEON;
  int i=0;
  while (!(RCC->BDCR & RCC_BDCR_LSERDY))
  {
    OsSleepMs(100);
    i++;
    if (i>50)
    {
      SysError("RTC XTAL did not stabilize.");
      break;
    }
    if (i%5) SysInfo("Waiting for RTC XTAL to stabilize...");
  }

  // enable RTC with external 32kHz xtal
  RCC->BDCR |= RCC_BDCR_RTCSEL_LSE;
  RCC->BDCR |= RCC_BDCR_RTCEN;
  RTC->CR &= (uint16_t)~0x0008; 
  //while (!(RTC->CR & 0x8));
  //while (!(RTC->CR & 0x20));
  RTC->CR |= RTC_CR_ALRAIE;
  //while (!(RTC->CR & 0x20));

  OsCreateTimer(RTC_Timer, NULL, OS_TIMER_PERIODIC, 100);
}

void RTC_SetTime(uint32_t time)
{
  (void) time;
  // TODO
  /*RTC_CheckXtal();
  rtcGetTime(&RTCD1, &timespec);*/

}

void RTC_SleepUntil(uint32_t wakeup_time)
{
  (void) wakeup_time;
  RTC_CheckXtal();
  // TODO
  /*
  alarmspec.tv_sec = wakeup_time;
  rtcSetAlarm(&RTCD1, 0, &alarmspec);
  rtcSetCallback(&RTCD1, rtc_callback);
  */
}



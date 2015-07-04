// Real-Time Clock Driver
// Copyright (c) 2014 Chris Merck

#include"RTC.h"
#define SYS_CURRENT_SUBSYS SYS_SUBSYS_OS
#include"Sys.h"
#include"hal.h"
#include"rtc.h"

static RTCDateTime timespec;
static RTCAlarm alarmspec;

static void rtc_callback(RTCDriver *rtcp, rtcevent_t event)
{
  (void) rtcp;
  (void) event;
}

void RTC_Init()
{
  // reset the backup domain
  PWR->CR |= PWR_CR_DBP;
  RCC->BDCR |= RCC_BDCR_BDRST;
  RCC->BDCR &= ~(RCC_BDCR_BDRST);

  rtcGetTime(&RTCD1, &timespec);

  // enable backup and pwr clocks
  RCC->APB1ENR |= RCC_APB1ENR_BKPEN;
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
  RTC->CRL &= (uint16_t)~0x0008; while (!(RTC->CRL & 0x8));
  while (!(RTC->CRL & 0x20));
  RTC->CRH |= RTC_CRH_ALRIE;
  while (!(RTC->CRL & 0x20));
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
  return timespec.tv_sec;
}

void RTC_SetTime(uint32_t time)
{
  RTC_CheckXtal();
  timespec.tv_sec = time;
  rtcGetTime(&RTCD1, &timespec);
}

void RTC_SleepUntil(uint32_t wakeup_time)
{
  RTC_CheckXtal();

  alarmspec.tv_sec = wakeup_time;
  rtcSetAlarm(&RTCD1, 0, &alarmspec);
  rtcSetCallback(&RTCD1, rtc_callback);

  //chSysLock();
  PWR->CR |= (PWR_CR_CSBF | PWR_CR_CWUF);
  PWR->CR &= ~(PWR_CR_PDDS | PWR_CR_LPDS);
  halPolledDelay(10000);
  SCB->SCR |= SCB_SCR_SLEEPDEEP_Msk;
  halPolledDelay(10000);
  /** Disabling for F030 until programmer is fixed... __WFI(); **/
}



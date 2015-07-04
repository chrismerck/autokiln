
#ifndef __RTC_H__
#define __RTC_H__

#include"ch.h"

void RTC_Init();
uint32_t RTC_GetTime();
void RTC_SetTime(uint32_t time);
void RTC_SleepUntil(uint32_t wakeup_time);

#endif //__RTC_H__

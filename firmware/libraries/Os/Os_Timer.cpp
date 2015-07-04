/** Os Abstraction Layer - Timer Tasks
 * Copyright (c) 2014 Chris Merck
 **/

#include"Os.h"
#define SYS_CURRENT_SUBSYS SYS_SUBSYS

#ifndef OS_TIMER_TASK_STACK
  #define OS_TIMER_TASK_STACK 2048
#endif

#ifndef OS_TIMER_MAX
  #define OS_TIMER_MAX  10
#endif

#ifndef SysError
  #include "stdio.h"
  #define SysError printf
#endif

struct os_timer_info_t
{
  void (*pEntryPoint)(void*);
  void * arg;
  os_timer_type_t type;
  unsigned int period_ms;
  int time_left;
};

static OsQueue * os_new_timer_q = NULL;
static os_lock_t * os_timer_lock;
static os_timer_info_t os_timers[OS_TIMER_MAX];

static void OsTimerTask(void* arg);

void OsTimerInit()
{
  os_new_timer_q = new OsQueue(1,"OsTimerQ");
  os_timer_lock = OsCreateLock();
  memset(os_timers,0,sizeof(os_timers));
  OsCreateTask(OsTimerTask,NULL,OS_PRI_NORMAL,OS_TIMER_TASK_STACK,"OsTimer");
}

static void OsTimerTask(void* arg)
{
  (void) arg;
  int dt;
  int t;
  unsigned int prev_t = OsGetMs();
  int next_i;
  int time_left_min;
  int wait_time;
  os_timer_info_t next_timer;
  while (true)
  {
    // compute dt
    t = OsGetMs();
    dt = OsGetMs() - prev_t;
    prev_t = t;
    dt = (dt>0)?dt:0;

    next_i = -1;
    next_timer.type = OS_TIMER_UNALLOC;
    time_left_min = 1000;
    OsLock(os_timer_lock);
    for (int i=0; i<OS_TIMER_MAX; i++)
    {
      if (os_timers[i].type != OS_TIMER_UNALLOC)
      {
        // tick down timer
        os_timers[i].time_left -= dt;
        // find most overdue timer, or at least next timer in line
        if (os_timers[i].time_left < time_left_min)
        {
          if (os_timers[i].time_left < 0)
          {
            next_i = i;
          }
          time_left_min = os_timers[i].time_left;
        }
      }
    }
    if (next_i>=0)
    {
      // save next timer info block so we can release lock
      memcpy((void*)&next_timer,(void*)&os_timers[next_i],sizeof(next_timer));

      // service timer structure
      os_timers[next_i].time_left = os_timers[next_i].period_ms;
      if (os_timers[next_i].type == OS_TIMER_ONESHOT)
      {
        os_timers[next_i].type = OS_TIMER_UNALLOC;
      }
    }
    else
    {
      memset((void*)&next_timer,0,sizeof(next_timer));
    }
#if 0
    printf("next_timer: dt=%d type=%d next_i=%d time_left=%d pEntryPoint=0x%08X arg=0x%08X period=%d time_left_min=%d\n",
        dt, next_timer.type, next_i, next_timer.time_left, next_timer.pEntryPoint, next_timer.arg, next_timer.period_ms,
        time_left_min);
#endif
    OsUnlock(os_timer_lock);

    if (next_i>=0)
    {
      // call the timer function
      next_timer.pEntryPoint(next_timer.arg);
      wait_time = 0;
    }
    else
    {
      if (time_left_min>0)
      {
        wait_time = time_left_min;
      }
      else
      {
        wait_time=1000;
      }
    }

    // sleep until next timer is ready to run,
    //  or we are signaled that there is a new timer
    os_new_timer_q->Dequeue(wait_time);
  }
}

os_timer_t* OsCreateTimer(void (*pEntryPoint)(void*), void* arg,
    os_timer_type_t type, unsigned int period_ms)
{
  os_timer_t * t = NULL;
  OsLock(os_timer_lock);
  for (int i=0;i<OS_TIMER_MAX;i++)
  {
    if (os_timers[i].type == OS_TIMER_UNALLOC)
    {
      os_timers[i].pEntryPoint = pEntryPoint;
      os_timers[i].arg = arg;
      os_timers[i].type = type;
      os_timers[i].period_ms = period_ms;
      os_timers[i].time_left = period_ms;
      t = (os_timer_t*) &os_timers[i];
      break;
    }
  }
  OsUnlock(os_timer_lock);
  if (!t)
  {
    SysError("OsCreateTimer: Too many timers (OS_TIMER_MAX)");
  }
  // wake timer task
  if (!os_new_timer_q->Enqueue((void*)1,1000))
  {
    SysError("OsCreateTimer failed to wake OsTimerTask.");
  }
  return t;
}


void OsDestroyTimer(os_timer_t * timer)
{
  OsLock(os_timer_lock);
  ((os_timer_info_t*)timer)->type = OS_TIMER_UNALLOC;
  OsUnlock(os_timer_lock);
}


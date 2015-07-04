#include"Watchdog.h"
#include"Os.h"

#define GSN_WATCHDOG_STACK  512

void Watchdog_EntryPoint(void * arg)
{
  ((Watchdog*) arg)->Task();
}

Watchdog::Watchdog()
{
}

bool Watchdog::Start()
{
  pTask = OsCreateTask(Watchdog_EntryPoint,this,
      OS_PRI_ABOVE_NORMAL,GSN_WATCHDOG_STACK,"WDG");
  return (pTask!=NULL);
}

void Watchdog::Task() 
{
  int count = 0;
  bool status = true;
  while (true) {
    count++;
    OsSleepMs(1000);

    TickHook_Project(status);
    HwPet_Project();
  }
}


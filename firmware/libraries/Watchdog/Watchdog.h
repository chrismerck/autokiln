#ifndef __WATCHDOG_H__
#define __WATCHDOG_H__

#include<stddef.h>

class Watchdog
{
public:
  Watchdog();
  bool Start();

private:
  void Task(); // __attribute__((noreturn));

  /*** Project-Specific ***/
  bool TickHook_Project(bool status);
  bool HwPet_Project();
  friend void Watchdog_EntryPoint(void * arg);

  void * pTask = NULL;
};

#endif // __WATCHDOG_H__


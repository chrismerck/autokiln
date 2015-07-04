// Debug Console Implementation
// Copyright (c) 2014,2015 Chris Merck

#include "ch.h"
#include "hal.h"
#include "chprintf.h"
#include "Os.h"
#define SYS_CURRENT_SUBSYS SYS_SUBSYS_DBG
#include "Sys.h"
#include"globals.h"
#include "DbgConsole.h"

#define DBG_CONSOLE_BAUDRATE  115200
#define DBG_CONSOLE_DRIVER    (&SD1)

/*===========================================================================*/
/* Private */
/*===========================================================================*/

static os_lock_t* lock;

static SerialConfig DbgConsoleCfg = 
{ 
  DBG_CONSOLE_BAUDRATE,
  0,
  USART_CR2_STOP1_BITS,
  0,
};

/*===========================================================================*/
/* Public */
/*===========================================================================*/
void DbgConsoleReInit() {
  sdStop(DBG_CONSOLE_DRIVER);
  sdStart(DBG_CONSOLE_DRIVER, &DbgConsoleCfg);
}
void DbgConsoleInit()
{
  DbgConsoleReInit();
  lock = OsCreateLock();
}

#define TLS_DBG_CONSOLE_LOCK_COUNT (chThdGetSelfX()->dbgConsoleLockCount)

/* recursive lock for console */
void DbgConsoleLock()
{
  if (TLS_DBG_CONSOLE_LOCK_COUNT == 0)
  {
    // lock the first time
    OsLock(lock);
  }
  // track numb
  TLS_DBG_CONSOLE_LOCK_COUNT++;
}

/* recursive lock for console */
void DbgConsoleUnlock()
{
  if (TLS_DBG_CONSOLE_LOCK_COUNT == 0)
  {
    // fatal error
    OsAssert(false, "dbgConsoleLockCount already zero");
  }
  else if (TLS_DBG_CONSOLE_LOCK_COUNT == 1)
  {
    OsUnlock(lock);
  }
  TLS_DBG_CONSOLE_LOCK_COUNT--;
}

/* ret true if actually printed */
bool DbgConsolePrintf(const char *fmt, ...) {
  va_list ap;
  BaseSequentialStream *chp = (BaseSequentialStream*) DBG_CONSOLE_DRIVER;
  va_start(ap, fmt);
  DbgConsoleLock();
  chvprintf(chp, fmt, ap);
  DbgConsoleUnlock();
  va_end(ap);
  return true;
}

size_t DbgConsoleWrite(uint8_t * data, size_t len)
{
  size_t r;
  BaseSequentialStream *chp = (BaseSequentialStream*) DBG_CONSOLE_DRIVER;
  DbgConsoleLock();
  r=chSequentialStreamWrite(chp,data,len);
  DbgConsoleUnlock();
  return r;
}

size_t DbgConsoleRead(uint8_t * data, size_t len, uint32_t timeout_ms)
{
  size_t c = 0;
  msg_t r;
  while (c<len)
  {
    r = DBG_CONSOLE_DRIVER->vmt->gett(DBG_CONSOLE_DRIVER,MS2ST(timeout_ms));
    if ((r == Q_TIMEOUT) || (r == Q_RESET))
    {
      // timeout
      break;
    }
    else
    {
      // got byte
      data[c] = (uint8_t) r;
      c++;
    }
  }

  // bytes read
  return c;
}


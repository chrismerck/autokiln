#ifndef __DBG_CONSOLE_H__
#define __DBG_CONSOLE_H__

#include<cstdint>
#include<cstddef>

void DbgConsoleInit();
void DbgConsoleReInit();
bool DbgConsolePrintf(const char *fmt, ...);
size_t DbgConsoleRead(uint8_t * data, size_t len, uint32_t timeout_ms);
size_t DbgConsoleWrite(uint8_t * data, size_t len);
void DbgConsoleLock();
void DbgConsoleUnlock();

#endif //__DBG_CONSOLE_H__

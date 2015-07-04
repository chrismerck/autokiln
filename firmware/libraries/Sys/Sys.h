/*
 * Sys Library Header
 * Copyright (c) 2014 Chris Merck
 */

#ifndef __SYS_H__
#define __SYS_H__


#include<stdint.h>
#include<cstring>
#include"Os.h"
#include"Sys_Project.h"
#define USE_TERMINAL_COLORS
#include"TerminalColors.h"

enum sys_dbg_lvl_t
{
  SYS_USER=0,  /* GREEN = user console output only */
  SYS_ERROR,   /* RED = critical condition */
  SYS_WARNING, /* YELLOW = abnormal / problematic condition */
  SYS_INFO,    /* WHITE = user-level interaction */
  SYS_DEBUG,   /* GREY = concise method-level info for developers */
  SYS_TRACE,   /* GREY = full packet dumps, rx/tx logs, verbose intra-method info */
  SYS_NOLEV=0xFF
};

// up to 255 subsystems may be defined
enum sys_subsys_t
{
  SYS_SUBSYS_MAIN=0,
  SYS_SUBSYS_WDG=1,
  SYS_SUBSYS_PEXP=2,
  SYS_SUBSYS_IDP=3,
  SYS_SUBSYS_SNAP=4,
  SYS_SUBSYS_XMP=5,
  SYS_SUBSYS_MODBUS=6,
  SYS_SUBSYS_EEPROM=7,
  SYS_SUBSYS_OS=8,
  SYS_SUBSYS_DIGIPOT=9,
  SYS_SUBSYS_UART=10,
  SYS_SUBSYS_POWER=11,
  SYS_SUBSYS_ADC=12,
  SYS_SUBSYS_SENSEPORT=13,
  SYS_SUBSYS_FLASH=14,
  SYS_SUBSYS_CRC=15,
  SYS_SUBSYS_UPDATER=16,
  SYS_SUBSYS_BOOTCTRL=17,
  SYS_SUBSYS_XBEE=18,
  SYS_SUBSYS_MOSQ=19,
  SYS_SUBSYS_DBG=20,
  SYS_SUBSYS_MAX,
};

extern bool DbgConsolePrintf(const char * fmt, ...);
extern size_t DbgConsoleWrite(uint8_t * data, size_t len);
extern size_t DbgConsoleRead(uint8_t * data, size_t len, uint32_t timeout_ms);
extern void DbgConsoleLock();
extern void DbgConsoleUnlock();
#if 0 // only if chibios gets recursive mutexes
#define SysDebugPrintLock DbgConsoleLock 
#define SysDebugPrintUnlock DbgConsoleUnlock
#endif
#define SysDebugPrintf  DbgConsolePrintf
#define SysDebugWrite   DbgConsoleWrite
#define SysDebugRead    DbgConsoleRead


#define SysUser(fmt,...)    SysLog(SYS_USER,KGRN,fmt,## __VA_ARGS__)
#define SysError(fmt,...)   SysLog(SYS_ERROR,KRED,fmt,## __VA_ARGS__)
#define SysWarning(fmt,...) SysLog(SYS_WARNING,KYEL,fmt,## __VA_ARGS__)
#define SysInfo(fmt,...)    SysLog(SYS_INFO,KNRM,fmt,## __VA_ARGS__)
#define SysDebug(fmt,...)   SysLog(SYS_DEBUG,KGRE,fmt,## __VA_ARGS__)
#define SysTrace(fmt,...)   SysLog(SYS_TRACE,KCYN,fmt,## __VA_ARGS__)

#define SysUserHexdump(data,len,fmt,...)    SysLogHexdump(SYS_USER,KGRN,data,len,fmt,## __VA_ARGS__)
#define SysErrorHexdump(data,len,fmt,...)   SysLogHexdump(SYS_ERROR,KRED,data,len,fmt,## __VA_ARGS__)
#define SysWarningHexdump(data,len,fmt,...) SysLogHexdump(SYS_WARNING,KYEL,data,len,fmt,## __VA_ARGS__)
#define SysInfoHexdump(data,len,fmt,...)    SysLogHexdump(SYS_INFO,KNRM,data,len,fmt,## __VA_ARGS__)
#define SysDebugHexdump(data,len,fmt,...)   SysLogHexdump(SYS_DEBUG,KGRE,data,len,fmt,## __VA_ARGS__)
#define SysTraceHexdump(data,len,fmt,...)   SysLogHexdump(SYS_TRACE,KCYN,data,len,fmt,## __VA_ARGS__)

#define SysUserPacket(pkt,fmt,...)    _SysPacketDump(SYS_USER,KGRN,pkt,fmt,## __VA_ARGS__)
#define SysErrorPacket(pkt,fmt,...)   _SysPacketDump(SYS_ERROR,KRED,pkt,fmt,## __VA_ARGS__)
#define SysWarningPacket(pkt,fmt,...) _SysPacketDump(SYS_WARNING,KYEL,pkt,fmt,## __VA_ARGS__)
#define SysInfoPacket(pkt,fmt,...)    _SysPacketDump(SYS_INFO,KNRM,pkt,fmt,## __VA_ARGS__)
#define SysDebugPacket(pkt,fmt,...)   _SysPacketDump(SYS_DEBUG,KGRE,pkt,fmt,## __VA_ARGS__)
#define SysTracePacket(pkt,fmt,...)   _SysPacketDump(SYS_TRACE,KCYN,pkt,fmt,## __VA_ARGS__)

#define SysAssert(cond)  \
  if (!cond) {\
    SysError("Failed Assertion: %s:%s",__FILE__,__LINE__);\
    SysHalt();\
  }

// for checking debug level
#define SysChkWarning()  (SysGetDebugLevel(SYS_CURRENT_SUBSYS)>=SYS_WARNING)
#define SysChkInfo()     (SysGetDebugLevel(SYS_CURRENT_SUBSYS)>=SYS_INFO)
#define SysChkDebug()    (SysGetDebugLevel(SYS_CURRENT_SUBSYS)>=SYS_DEBUG)


// TODO: Why does this generate a "comparison is always true",
//  when infact it is working fine?
#pragma GCC diagnostic ignored "-Wtype-limits" // TODO: Remove this!
#define SysLogNoLevelCheck(level,color,fmt,...) \
  SysDebugPrintf(color "%10d: %s: %s: " fmt KNRM "\r\n", \
    OsGetMs(),sys_dbg_lvl_prefix[level],sys_subsys_name[SYS_CURRENT_SUBSYS],## __VA_ARGS__)
#define SysLog(level,color,fmt,...) \
  if (SysGetDebugLevel(SYS_CURRENT_SUBSYS)>=level) \
    SysLogNoLevelCheck(level,color,fmt,## __VA_ARGS__)
#define SysLogHexdump(level,color,data,len,fmt,...) \
  if (SysGetDebugLevel(SYS_CURRENT_SUBSYS)>=level) { \
    DbgConsoleLock(); \
    SysLogNoLevelCheck(level,color,fmt,## __VA_ARGS__); \
    SysDebugPrintf(color); \
    SysHexdump(data,len); \
    SysDebugPrintf(KNRM); \
    DbgConsoleUnlock(); \
  } \
  (void) data
#define _SysPacketDump(level,color,pkt,fmt,...) \
  if (SysGetDebugLevel(SYS_CURRENT_SUBSYS)>=level) { \
    DbgConsoleLock(); \
    SysLogNoLevelCheck(level,color,fmt,## __VA_ARGS__); \
    SysDebugPrintf(color); \
    SysPacketDump(pkt); \
    SysDebugPrintf(KNRM); \
    DbgConsoleUnlock(); \
  } \
  (void) pkt

extern const char * sys_dbg_lvl_prefix[];
extern const char * sys_subsys_name[];
sys_dbg_lvl_t SysGetDebugLevel(sys_subsys_t s);
void SysSetDebugLevel(sys_subsys_t s, sys_dbg_lvl_t level);
void SysDefaultDebugLevels();
void SysHexdump(const uint8_t * buf, uint32_t len);

/* command handler defines */

typedef bool (*sys_cmd_handler_t)(
    const uint8_t * cmd, 
    uint8_t * in_data, uint32_t in_len, 
    uint8_t * out_data, uint32_t out_len_max, uint32_t * out_len);

struct sys_cmd_handler_entry {
  sys_cmd_handler_entry(sys_subsys_t subsys,sys_cmd_handler_t handler) {
    this->subsys=subsys;
    this->handler=handler;
  }
  sys_subsys_t subsys = SYS_SUBSYS_MAX;
  sys_cmd_handler_t handler = NULL;
};

bool SysCommand(sys_subsys_t s, 
    const uint8_t * cmd, 
    uint8_t * in_data, uint32_t in_len, 
    uint8_t * out_data, uint32_t out_len_max, uint32_t * out_len);

bool SysCommand(sys_subsys_t s, const uint8_t * cmd);


/** defined somewhere by project **/
//bool SysDebugPrintf(const char * fmt, ...);

#endif //__SYS_H__


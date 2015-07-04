/*
 * Sys Library
 * Copyright (c) 2014 Chris Merck
 */

#include"Sys.h"
#include<stdint.h>

const char * sys_dbg_lvl_prefix[] =
{
  "USER ",
  "ERROR",
  "WARN ",
  "INFO ",
  "DEBUG",
  "TRACE",
};

const char * sys_subsys_name[] =
{
  "MAIN", // 0
  "WDG ", // 1
  "PEXP", // 2
  "IDP ", // 3
  "SNAP", // 4
  "XMP ", // 5
  "MBUS", // 6
  "EEPM", // 7
  "OS  ", // 8 
  "DPOT", // 9
  "UART", // 10
  "PWR ", // 11
  "ADC ", // 12
  "SP  ", // 13
  "FLSH", // 14
  "CRC ", // 15
  "UPDT", // 16
  "BOOT", // 17
  "XBEE", // 18
  "MOSQ", // 19
  "DBG ", // 20
};

void SysDefaultDebugLevels()
{
  // by default only report warnings and errors
  for (int i=0;i<SYS_SUBSYS_MAX;i++)
  {
    SysSetDebugLevel((sys_subsys_t)i,SYS_WARNING);
  }
}

static uint8_t sys_dbg_lvls[SYS_SUBSYS_MAX] = {}; // init to 0 (c++)

sys_dbg_lvl_t SysGetDebugLevel(sys_subsys_t s)
{
  return (sys_dbg_lvl_t) sys_dbg_lvls[s];
}

void SysSetDebugLevel(sys_subsys_t s, sys_dbg_lvl_t level)
{
  sys_dbg_lvls[s] = (uint8_t) level;
}

void SysHexdump(const uint8_t * buf, uint32_t len)
{
  uint32_t offset = 0;
  char c;

  DbgConsoleLock();

  while (offset<len)
  {
    // offset
    SysDebugPrintf("%08X  ",offset);

    // hex
    for (unsigned int i = 0; i<16; i++)
    {
      if (offset+i<len)
      {
        SysDebugPrintf("%02X ", buf[offset+i]);
      }
      else
      {
        SysDebugPrintf("   ");
      }
      // gap between sets of 8 bytes
      if (i==7)
      {
        SysDebugPrintf(" ");
      }
    }

    // ascii
    SysDebugPrintf(" |");
    for (unsigned int i = 0; i<16; i++)
    {
      if (offset+i<len)
      {
        c = buf[offset+i];
        if (!(c>=0x20/*space*/ && c<=0x7E/*tilde*/)) // non-printable
        {
          c='.';
        }
        SysDebugPrintf("%c",c);
      }
      else
      {
        break;
      }
    }
    SysDebugPrintf("|\r\n");

    offset += 16;
  }

  DbgConsoleUnlock();
}

/* table defined by Sys_Project.cpp */
extern sys_cmd_handler_entry sys_cmd_handler_table[];

/**
 * find command handler for specified subsystem and execute 
 * cmd = null-terminated string such as "cp" for "counters print"
 * RETURN true on successful command handling
 **/
bool SysCommand(sys_subsys_t s, 
    const uint8_t * cmd, 
    uint8_t * in_data, uint32_t in_len, 
    uint8_t * out_data, uint32_t out_len_max, uint32_t * out_len)
{
  for (int i=0;;i++) {
    sys_cmd_handler_entry e = sys_cmd_handler_table[i];
    if (e.subsys == SYS_SUBSYS_MAX) return false;
    if (e.subsys == s) {
      if (!e.handler) return false;
      return e.handler(cmd,in_data,in_len,out_data,out_len_max,out_len);
    }
  }
}

/* short version */
bool SysCommand(sys_subsys_t s, 
    const uint8_t * cmd) {
  return SysCommand(s,cmd,NULL,0,NULL,0,NULL);
}


#ifndef __NV_H__
#define __NV_H__
#include"Os.h"

void NV_Init();
void NV_Load();
void NV_Save();
void NV_Check();

enum nv_type_t {
  NV_TYPE_NONE,    // terminator
  NV_TYPE_BOOL,    // on / off ("%s")
  NV_TYPE_INT,     // whole number  ("%ld")
  NV_TYPE_FIX10,   // fixed-point decimal ("%ld.%01ld")
  NV_TYPE_FIX100,  // fixed-point decimal ("%ld.%02ld")
  NV_TYPE_FIX1000, // fixed-point decimal ("%ld.%03ld")
};

struct NVInfoItem {
  nv_type_t type; // controls display (all nv params are int32_t)
  const char* name;   // up to 20 characters 
  const char* unit;   // up to 10 chars
  int32_t def;  // default value (on RESET pressed or EEPROM read fail)
};

enum nv_param_t {
  NV_PARAM_MC24H = 0,
  NV_PARAM_DH_MIN_REST_TIME,
  NV_PARAM_DH_MIN_RUN_TIME,
  NV_PARAM_LC1_OFFSET,
  NV_PARAM_LC1_SCALE,
  NV_PARAM_LC2_OFFSET,
  NV_PARAM_LC2_SCALE,
  NV_PARAM_LC3_OFFSET,
  NV_PARAM_LC3_SCALE,
  NV_PARAM_LC4_OFFSET,
  NV_PARAM_LC4_SCALE,
  NV_PARAM_MAX,
};

const NVInfoItem NVInfo[] = {
  {NV_TYPE_FIX10,   "TARGET 24H MC CHANGE", "\%",         -20}, 
  {NV_TYPE_INT,     "DEHUM MIN REST TIME",  "sec",        60}, 
  {NV_TYPE_INT,     "DEHUM MIN RUN TIME",   "sec",        60}, 
  {NV_TYPE_FIX1000, "LOAD CELL 1 OFFSET",   "mV",         0}, 
  {NV_TYPE_FIX1000, "LOAD CELL 1 SCALE",    "mV/FS",      15000}, 
  {NV_TYPE_FIX1000, "LOAD CELL 2 OFFSET",   "mV",         0}, 
  {NV_TYPE_FIX1000, "LOAD CELL 2 SCALE",    "mV/FS",      15000}, 
  {NV_TYPE_FIX1000, "LOAD CELL 3 OFFSET",   "mV",         0}, 
  {NV_TYPE_FIX1000, "LOAD CELL 3 SCALE",    "mV/FS",      15000}, 
  {NV_TYPE_FIX1000, "LOAD CELL 4 OFFSET",   "mV",         0}, 
  {NV_TYPE_FIX1000, "LOAD CELL 4 SCALE",    "mV/FS",      15000}, 
  {NV_TYPE_NONE, "", "", 0},
}; 

extern int32_t NVParam[NV_PARAM_MAX];

#endif // __NV_H__

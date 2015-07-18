#include"NV.h"
#include"Os.h"

int32_t NVParam[NV_PARAM_MAX];

void NV_Init() {
  OsZero((void*)NVParam,sizeof(NVParam));
}

void NV_Load(){}
void NV_Save(){}
void NV_Check(){}



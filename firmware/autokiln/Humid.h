#ifndef __HUMID_H__
#define __HUMID_H__

void Humid_Init();
int32_t Get_RH(int32_t sensor);
int32_t Get_T(int32_t sensor);

#define HUMID_NUM_SENSORS 2
#define HUMID_DATA_BYTES 5

extern int32_t humid_RH[HUMID_NUM_SENSORS];
extern int32_t humid_T[HUMID_NUM_SENSORS];
extern bool new_humid[HUMID_NUM_SENSORS];

extern uint8_t humid_data[HUMID_NUM_SENSORS][HUMID_DATA_BYTES];

#endif // __HUMID_H__

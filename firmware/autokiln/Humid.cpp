#include"hal.h"
#include"Humid.h"
#include"Os.h"

#define HUMID_READ_PERIOD_MS  2500

int32_t humid_RH[2];
int32_t humid_T[2];

/*** Humidity Sensor ISR ***/

void extcb_humid(EXTDriver *extp, expchannel_t channel) {
  (void)extp;
  (void)channel;
  chSysLockFromISR();
  /* todo */
  chSysUnlockFromISR();
}

static void Humid_Timer_CB(void* arg) {
  (void) arg;
  /* end master pulse */
  setPin(PPIN_HUMID_DATA1);
  setPin(PPIN_HUMID_DATA2);
}

static virtual_timer_t humid_vt;

static void Humid_Timer(void* arg) {
  (void) arg;

  /* check for reading from ISR */
  // TODO

  /* send master pulse (2ms) to trigger another read */
  clearPin(PPIN_HUMID_DATA1);
  clearPin(PPIN_HUMID_DATA2);
  chSysLock();
  chVTSetI(&humid_vt, MS2ST(2), Humid_Timer_CB, NULL);
}


/**
 * Public Interface
 **/

int32_t Get_RH(int32_t sensor) {
  if (!(sensor == 0) || (sensor == 1)) return 0;
  return humid_RH[sensor];
}

int32_t Get_T(int32_t sensor) {
  if (!(sensor == 0) || (sensor == 1)) return 0;
  return humid_T[sensor];
}

void Humid_Init() {
  OsCreateTimer(Humid_Timer, NULL, OS_TIMER_PERIODIC, HUMID_READ_PERIOD_MS);
}


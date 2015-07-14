#include"hal.h"
#include"Humid.h"
#include"Os.h"

#define HUMID_READ_PERIOD_MS  2500

#define HUMID_DATA_BYTES 5


/* 
 * public state variables
 * in fixed-point, single decimal place
 */
int32_t humid_RH[HUMID_NUM_SENSORS];
int32_t humid_T[HUMID_NUM_SENSORS];
bool new_humid[HUMID_NUM_SENSORS];

/*
 * private state variables
 */
int32_t humid_bit[HUMID_NUM_SENSORS];
uint8_t humid_data[HUMID_NUM_SENSORS][HUMID_DATA_BYTES];
bool humid_pin[HUMID_NUM_SENSORS];
int16_t humid_cnt[HUMID_NUM_SENSORS];
int16_t pulse_lens[HUMID_DATA_BYTES*8];

int16_t isr_max_time = 0;


/*** Humidity Sensor ISR ***/

#define HUMID_NEG_BIT_MASK ((uint8_t)0x80)

void extcb_humid(EXTDriver *extp, expchannel_t channel) {
  (void)extp;
  (void)channel;
  bool new_humid_pin[HUMID_NUM_SENSORS];
  int16_t pulse_len;
  int16_t isr_start_time = TIM6->CNT;
  chSysLockFromISR();
  new_humid_pin[0] = readPin(PPIN_HUMID_DATA1);
  new_humid_pin[1] = readPin(PPIN_HUMID_DATA2);
  for (int i=0; i<2; i++) {
    if (new_humid_pin[i] && !humid_pin[i]) {
      /* got leading-edge of pulse */
      // start counting
      humid_cnt[i] = TIM6->CNT;
      if (humid_bit[i] == HUMID_DATA_BYTES*8) {
        /* got 4 bytes plus checksum */
        humid_bit[i]++; // mark as finished
        /* confirm checksum */
        if (humid_data[i][4] == humid_data[i][0] + humid_data[i][1] 
            + humid_data[i][2] + humid_data[i][3]) {
          /* checksum correct, save */
          humid_RH[i] = ((int32_t)(humid_data[i][0])<<8) + humid_data[i][1];
          bool negT = (humid_data[i][2] & HUMID_NEG_BIT_MASK);
          humid_T[i] = (negT?-1:1)*(((int32_t)(humid_data[i][2] & ~HUMID_NEG_BIT_MASK)<<8) + humid_data[i][3]);
          new_humid[i] = true;
        }
      } 
    }
    if (!new_humid_pin[i] && humid_pin[i]) {
      /* got trailing-edge of pulse */
      // determine length (in microseconds)
      if ((humid_bit[i]/8<HUMID_DATA_BYTES)) {
        if (humid_bit[i] >= 0) {
          pulse_len = TIM6->CNT - humid_cnt[i];
          pulse_lens[humid_bit[i]] = pulse_len;
          /* add bit to humid_data, msb first */
          humid_data[i][humid_bit[i]/8] |= ((pulse_len>50?1:0) << (8-(humid_bit[i]%8)));
        } else {
          /* ignore first bit, which is just ACK */
        }
        humid_bit[i]++;
      }
    }
    humid_pin[i] = new_humid_pin[i];
  }
  int16_t isr_run_time = TIM6->CNT - isr_start_time;
  isr_max_time = (isr_run_time > isr_max_time)?isr_run_time:isr_max_time;
  chSysUnlockFromISR();
}

static void Humid_Reset_ISR_State() {
  int i;
  for (i=0;i<HUMID_NUM_SENSORS;i++) {
    humid_bit[i] = -1;
    humid_pin[i] = false;
    humid_cnt[i] = 0;
    OsZero((void*)humid_data[i],HUMID_DATA_BYTES);
  }
}

static void Humid_Timer_CB(void* arg) {
  (void) arg;
  /* end master pulse */ 
  chSysLockFromISR();
  TIM6->CNT = 0; // reset pulse timer
  Humid_Reset_ISR_State();
  setPin(PPIN_HUMID_DATA1);
  setPin(PPIN_HUMID_DATA2);
  chSysUnlockFromISR();
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
  chSysUnlock();
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

#define  RCC_APB1ENR_TIM6EN                  ((uint32_t)0x00000010)        /*!< TIM6 clock enable */
#define  RCC_APB1ENR_TIM7EN                  ((uint32_t)0x00000020)        /*!< TIM7 clock enable */

void Humid_Init() {
  /* configure timer */
  rccEnableAPB1(RCC_APB1ENR_TIM6EN, false);
  TIM6->PSC = 0x0024; /* 1us ticks */
  TIM6->ARR = 0xFFFF;
  TIM6->CR1 = TIM_CR1_CEN /*enable*/;

  OsCreateTimer(Humid_Timer, NULL, OS_TIMER_ONESHOT, HUMID_READ_PERIOD_MS);
}


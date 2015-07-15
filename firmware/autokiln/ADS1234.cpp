#include "ADS1234.h"
#include "hal.h"
#include "Os.h"

/*
 * TODO:
 *  
 *   Make ISR triggered on falling edge of DOUT
 *     round-robin between four channels,
 *     saving to state variables
 *
 *   write getter function
 *
 */


/* 
 * project-specific functions
 */

static bool ADS1234_Read_DOUT_Project() {
  return readPin(PPIN_ADC_DOUT);
}

static void ADS1234_Set_SCLK_Project() {
  setPin(PPIN_ADC_SCLK);
}

static void ADS1234_Init_Project() {
  setPin(PPIN_ADC_PDWN);
  setPin(PPIN_ADC_SCLK);
}

static void ADS1234_Clear_SCLK_Project() {
  clearPin(PPIN_ADC_SCLK);
}

static void ADS1234_Select_Channel_Project(int32_t ch) {
  /* set the address pins accordingly */
  switch (ch) {
    case 0:
      clearPin(PPIN_ADC_A0);
      clearPin(PPIN_ADC_A1);
      break;
    case 1:
      setPin(PPIN_ADC_A0);
      clearPin(PPIN_ADC_A1);
      break;
    case 2:
      clearPin(PPIN_ADC_A0);
      setPin(PPIN_ADC_A1);
      break;
    case 3:
      setPin(PPIN_ADC_A0);
      setPin(PPIN_ADC_A1);
      break;
  }
}

int32_t ADS1234_Read(int32_t ch) {
  int32_t i;
  int32_t data = 0;
  ADS1234_Select_Channel_Project(ch);
  /* send 24 clock pulses */
  for (i=23; i>=0; i--) {
    /* i = bit number */
    ADS1234_Set_SCLK_Project();
    if (ADS1234_Read_DOUT_Project()) data |= 1 << i;
    ADS1234_Clear_SCLK_Project();
  }
  /* convert from two's complement to negative numbers */
  if (data>0x7FFFFF) data -= 0x1000000;
  /* send 25th pulse to reset DRDY indication */
  ADS1234_Set_SCLK_Project();
  ADS1234_Clear_SCLK_Project();
  return data;
}


void ADS1234_Timer(void * arg) {
  (void) arg;
  ADS1234_Read(0);
}


/*
 * public interface
 */

void ADS1234_Init() {
  ADS1234_Init_Project();
  OsCreateTimer(ADS1234_Timer, NULL, OS_TIMER_PERIODIC, 1000);
}



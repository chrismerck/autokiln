
#include "hal.h"
#include "Input.h"
#include "LCD.h"
#include "Os.h"
#include<cstdio>
#include<cstdlib>

#include"Humid.h"

extern int16_t isr_max_time;
extern uint8_t humid_data[2][5];
extern int32_t humid_bit[2];
extern int16_t pulse_len;
extern int16_t pulse_lens[5*8];

int32_t but_click, but_manual, but_menu, but_reset;
int32_t enc_delta;
int32_t enc_cnt = 0;

int32_t click = 0;
int32_t enc_delta_isr = 0;

#define ENC_STATE_Z   0
#define ENC_STATE_A   1
#define ENC_STATE_B   2
#define ENC_STATE_AB  3
int32_t enc_state = ENC_STATE_AB;
bool enc_token = false;


/**
 * User Input Event Hooks
 * (Return quickly!)
 **/

void Input_Click_Down() {
  sprintf((char*)lcd_buf,"CLICK DOWN     ");
  LCD_Redraw();
}

void Input_Click_Up() {
  sprintf((char*)lcd_buf,"CLICK UP       ");
  LCD_Redraw();
}

void Input_Manual_Down() {
  sprintf((char*)lcd_buf,"MANUAL DOWN    ");
  LCD_Redraw();
}

void Input_Manual_Up() {
  sprintf((char*)lcd_buf,"MANUAL UP      ");
  LCD_Redraw();
}

void Input_Menu_Down() {
  sprintf((char*)lcd_buf,"MENU  DOWN     ");
  LCD_Redraw();
}

void Input_Menu_Up() {
  sprintf((char*)lcd_buf,"MENU  UP       ");
  LCD_Redraw();
}

void Input_Reset_Down() {
  sprintf((char*)lcd_buf,"RESET DOWN     ");
  LCD_Redraw();
}

void Input_Reset_Up() {
  sprintf((char*)lcd_buf,"RESET UP       ");
  LCD_Redraw();
}

void Input_Encoder(int32_t delta) {
  enc_cnt += delta;
  sprintf((char*)lcd_buf,"ENC   %9ld %ld",delta,enc_cnt);
  LCD_Redraw();
}

/**
 * Private Task
 ***/

#define INPUT_EVENT_DOWN   1
#define INPUT_EVENT_UP    -1
#define INPUT_EVENT_NONE   0

#define INPUT_STATE_UP  0
#define INPUT_STATE_WAIT_DOWN  1
#define INPUT_STATE_DOWN  2
#define INPUT_STATE_WAIT_UP  3

int32_t Input_Debounce(bool pin, int32_t * state) {
  /* returns:
   *   1  =  down
   *   0  =  nothing
   *  -1  =  up
   */

  switch (*state) {
    case INPUT_STATE_UP:
      if (pin) *state = INPUT_STATE_WAIT_DOWN;
      break;
    case INPUT_STATE_WAIT_DOWN:
      if (pin) { *state = INPUT_STATE_DOWN; return INPUT_EVENT_DOWN; } else *state = INPUT_STATE_UP;
      break;
    case INPUT_STATE_DOWN:
      if (!pin) *state = INPUT_STATE_WAIT_UP; 
      break;
    case INPUT_STATE_WAIT_UP:
      if (!pin) { *state = INPUT_STATE_UP; return INPUT_EVENT_UP; } else *state = INPUT_STATE_UP;
      break;
  }

  return INPUT_EVENT_NONE;
}

void Input_Task(void * arg) {
  arg = arg;
  int32_t event;
  while (true) {
    event = Input_Debounce(!readPin(PPIN_MENU), &but_menu);
    if (event == INPUT_EVENT_DOWN) Input_Menu_Down();
    if (event == INPUT_EVENT_UP) Input_Menu_Up(); 
    event = Input_Debounce(!readPin(PPIN_MANUAL), &but_manual);
    if (event == INPUT_EVENT_DOWN) Input_Manual_Down();
    if (event == INPUT_EVENT_UP) Input_Manual_Up(); 
    event = Input_Debounce(!readPin(PPIN_RESET), &but_reset);
    if (event == INPUT_EVENT_DOWN) Input_Reset_Down();
    if (event == INPUT_EVENT_UP) Input_Reset_Up(); 
    event = Input_Debounce(!readPin(PPIN_ENC_CLICK), &but_click);
    if (event == INPUT_EVENT_DOWN) Input_Click_Down();
    if (event == INPUT_EVENT_UP) Input_Click_Up(); 

    /* read encoder turn from interrupt routine */
    OsSysLock();
    if (enc_delta_isr != 0) {
      enc_delta = enc_delta_isr;
      enc_delta_isr = 0;
    }
    OsSysUnlock();
    if (enc_delta != 0) { 
      Input_Encoder(enc_delta);
      enc_delta = 0;
    }

    sprintf((char*)&lcd_buf[0*LCD_XMAX],"RH %3ld.%ld%%  T %3ld.%ldC",
        humid_RH[0]/10, humid_RH[0]%10,
        humid_T[0]/10, humid_T[0]%10
        );


    sprintf((char*)&lcd_buf[1*LCD_XMAX],"RH %3ld.%ld%%  T %3ld.%ldC",
        humid_RH[1]/10, humid_RH[1]%10,
        humid_T[1]/10, humid_T[1]%10
        );

    /*
    sprintf((char*)&lcd_buf[0*LCD_XMAX],
        "%d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d ISR %d us",
        pulse_lens[0],
        pulse_lens[1],
        pulse_lens[2],
        pulse_lens[3],
        pulse_lens[4],
        pulse_lens[5],
        pulse_lens[6],
        pulse_lens[7],
        pulse_lens[8 ],
        pulse_lens[9 ],
        pulse_lens[10],
        pulse_lens[11],
        pulse_lens[12],
        pulse_lens[13],
        pulse_lens[14],
        pulse_lens[15],
        isr_max_time);
        */

    sprintf((char*)&lcd_buf[3*LCD_XMAX],"hum %02X%02X %02X%02X %02X b%02lX",
        humid_data[0][0],
        humid_data[0][1],
        humid_data[0][2],
        humid_data[0][3],
        humid_data[0][4],
        humid_bit[0]
        );

    LCD_Redraw();

    OsSleepMs(5);
  }
}

void extcb_enc(EXTDriver *extp, expchannel_t channel) {
  (void)extp;
  (void)channel;
  int32_t new_enc_state;
  chSysLockFromISR();
  click++;
  new_enc_state = (readPin(PPIN_ENC_A)) | (readPin(PPIN_ENC_B) << 1);
  if (new_enc_state != enc_state) {
    switch (enc_state) {
      case ENC_STATE_AB:
        enc_token = true;
        break;
      case ENC_STATE_B:
        if (enc_token && (new_enc_state == ENC_STATE_Z)) {
          enc_delta_isr++;
          enc_token = false;
        }
        break;
      case ENC_STATE_A:
        if (enc_token && (new_enc_state == ENC_STATE_Z)) {
          enc_delta_isr--;
          enc_token = false;
        }
        break;
    }
  }
  enc_state = new_enc_state;
  chSysUnlockFromISR();
}


/***
 * PUBLIC INTERFACE
 ***/

void Input_Init() {
  but_click = but_manual = but_menu = but_reset = 0;
  enc_delta_isr = 0;
  enc_delta = 0;
  OsCreateTask(Input_Task, NULL, OS_PRI_NORMAL, 2048, "Input");
}



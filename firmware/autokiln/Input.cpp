
#include "hal.h"
#include "Input.h"
#include "LCD.h"
#include "Os.h"
#include "Menu.h"
#include<cstdio>
#include<cstdlib>

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
  g_pCurrentMenu->Input(INPUT_TYPE_CLICK,INPUT_EVENT_DOWN);
  LCD_Backlight_Wake();
}

void Input_Click_Up() {
  g_pCurrentMenu->Input(INPUT_TYPE_CLICK,INPUT_EVENT_UP);
  LCD_Backlight_Wake();
}

void Input_Manual_Down() {
  g_pCurrentMenu->Input(INPUT_TYPE_MANUAL,INPUT_EVENT_DOWN);
  LCD_Backlight_Wake();
}

void Input_Manual_Up() {
  g_pCurrentMenu->Input(INPUT_TYPE_MANUAL,INPUT_EVENT_UP);
  LCD_Backlight_Wake();
}

void Input_Menu_Down() {
  g_pCurrentMenu->Input(INPUT_TYPE_MENU,INPUT_EVENT_DOWN);
  LCD_Backlight_Wake();
}

void Input_Menu_Up() {
  g_pCurrentMenu->Input(INPUT_TYPE_MENU,INPUT_EVENT_UP);
  LCD_Backlight_Wake();
}

void Input_Reset_Down() {
  g_pCurrentMenu->Input(INPUT_TYPE_RESET,INPUT_EVENT_DOWN);
  LCD_Backlight_Wake();
}

void Input_Reset_Up() {
  g_pCurrentMenu->Input(INPUT_TYPE_RESET,INPUT_EVENT_UP);
  LCD_Backlight_Wake();
}

void Input_Encoder(int32_t delta) {
  /*** Holding down the MANUAL button while scrolling increases speed by 50x ***/
  if (but_manual) delta *= 50;

  g_pCurrentMenu->Input(INPUT_TYPE_ENCODER,delta);
  LCD_Backlight_Wake();
}

/**
 * Private Task
 ***/
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

    /* check for button presses */
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

    /* redraw screen if needed */
    if (g_pCurrentMenu->Need_Redraw()) {
      g_pCurrentMenu->Redraw();
    }

    LCD_Backlight_Tick();

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




#include "hal.h"
#include "Input.h"
#include "LCD.h"
#include "Os.h"
#include<cstdio>
#include<cstdlib>

int32_t but_click, but_manual, but_menu, but_reset;
int32_t enc_state, enc_a, enc_b;
int32_t enc_delta;

extern int32_t click;

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
  sprintf((char*)lcd_buf,"ENC   %9ld",delta);
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

    sprintf((char*)&lcd_buf[3*LCD_XMAX],"click %ld",click);
    LCD_Redraw();

    OsSleepMs(5);
  }
}

/***
 * PUBLIC INTERFACE
 ***/

void Input_Init() {
  but_click = but_manual = but_menu = but_reset = 0;
  enc_delta = 0;
  enc_state = 0;
  OsCreateTask(Input_Task, NULL, OS_PRI_ABOVE_NORMAL, 1024, "Input");
}



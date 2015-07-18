#include"Menu.h"
#include"LCD.h"
#include"Humid.h"
#include "hal.h"
#include "Input.h"
#include "Os.h"
#include<cstdio>
#include<cstdlib>

int32_t abs_i32(int32_t x) {
  return (x>0)?x:-x;
}

MenuBase * g_pCurrentMenu;
MenuMain * g_pMenuMain;

MenuBase::MenuBase() {
}

/***
 * Main Screen 
 ***
 *
 *   0         1
 *   01234567890123456789
 *  /--------------------\
 * 0|IW 3000 IM 29.0 24H |
 * 1|CW 1000 CM 14.5 -2.0|
 * 2|E 104F 28% MODE AUTO|
 * 3|I 115F 60% 114F 50% |
 *  \--------------------/
 *  
 */

MenuMain::MenuMain() {
}


void MenuMain::Input(input_type_t type, int32_t arg) {
  (void) type;
  (void) arg;
  switch (type) {
    case INPUT_TYPE_ENCODER:
      break;
    default:
      break;
  }
  need_redraw = true;
}

int32_t weight_ini = 10240;
int32_t weight_curr = 7890;
int32_t mc_ini = 800;
int32_t mc_curr = 123;
int32_t mc_delta = -21;
int32_t T_target = 1130;
int32_t RH_target = 250;

void MenuMain::Redraw() {
  sprintf((char*)&lcd_buf[0*LCD_XMAX],
      "IW%5ld IM %02ld.%1ld 24H ",
      weight_ini/10, mc_ini/10, mc_ini%10);

  sprintf((char*)&lcd_buf[1*LCD_XMAX],
      "CW%5ld CM %02ld.%1ld %2ld.%ld",
      weight_curr/10, mc_curr/10, mc_curr%10, 
      mc_delta/10, abs_i32(mc_delta)%10);

  sprintf((char*)&lcd_buf[2*LCD_XMAX],
      "E %3ldF%3ld%% MODE xxx",
      humid_T[1]/10, humid_RH[1]/10);

  sprintf((char*)&lcd_buf[3*LCD_XMAX],
      "I %3ldF%3ld%% %3ldF%3ld%%",
      humid_T[0]/10, humid_RH[0]/10,
      T_target/10, RH_target/10);

  LCD_Redraw();
  need_redraw = false;
}

/***
 * History Screen
 ***
 *
 *   0         1
 *   01234567890123456789
 *  /--------------------\
 * 0|00d00h 104F 20% 14.5|
 * 1|00d06h 104F 20% 14.5|
 * 2|00d12h 104F 20% 14.5|
 * 3|00d18h 104F 20% 14.5|
 *  \--------------------/
 *
 *  Displays average internal temp, RH, and MC.
 *  
 */



/***
 * Settings Menu
 ***
 *
 *   0         1
 *   01234567890123456789
 *  /--------------------\
 * 0|01 Setting  10.00 A |
 * 1|02 Setting  10.00 lb|
 * 2|03 Setting 210.00 V |
 * 3|04 Setting  10.00 A |
 *  \--------------------/
 *  
 */





/***
 * initialize menus
 ***/
void Menu_Init() {
  g_pMenuMain = new MenuMain();
  g_pCurrentMenu = g_pMenuMain;
}


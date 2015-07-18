#include"Menu.h"
#include"LCD.h"
#include"Humid.h"
#include "hal.h"
#include "Input.h"
#include "Os.h"
#include "NV.h"
#include<cstdio>
#include<cstdlib>
#include"RTC.h"

MenuBase * g_pCurrentMenu;
MenuMain * g_pMenuMain;
MenuHist * g_pMenuHist;
MenuConfig * g_pMenuConfig;

int32_t abs_i32(int32_t x) {
  return (x>0)?x:-x;
}

static void NextMenu() {
  if (g_pCurrentMenu == g_pMenuMain) g_pCurrentMenu = g_pMenuHist;
  else if (g_pCurrentMenu == g_pMenuHist) g_pCurrentMenu = g_pMenuConfig;
  else if (g_pCurrentMenu == g_pMenuConfig) g_pCurrentMenu = g_pMenuMain;
  g_pCurrentMenu->Redraw();
}


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
    case INPUT_TYPE_MENU:
      if (arg == INPUT_EVENT_DOWN) {
        NextMenu();
        return;
      }
      break;
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

  LCD_ClearBuffer();
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

MenuHist::MenuHist() {
}


void MenuHist::Input(input_type_t type, int32_t arg) {
  (void) type;
  (void) arg;
  switch (type) {
    case INPUT_TYPE_MENU:
      if (arg == INPUT_EVENT_DOWN) {
        NextMenu();
        return;
      }
      break;
    case INPUT_TYPE_ENCODER:
      break;
    default:
      break;
  }
  need_redraw = true;
}

void MenuHist::Redraw() {

  LCD_ClearBuffer();
  sprintf((char*)&lcd_buf[0*LCD_XMAX],
      "HIST");

  /*
  sprintf((char*)&lcd_buf[1*LCD_XMAX],
      "CW%5ld CM %02ld.%1ld %2ld.%ld",
      weight_curr/10, mc_curr/10, mc_curr%10, 
      mc_delta/10, abs_i32(mc_delta)%10);
      */
  sprintf((char*)&lcd_buf[1*LCD_XMAX],
      "TIME %ld", RTC_GetTime());

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
 * Settings Menu
 ***
 *
 *   0         1
 *   01234567890123456789
 *  /--------------------\
 * 0|CONFIG ITEM #001    |
 * 1|LOAD CELL 1 SCALE   |
 * 2|100.23478   uV/ton  |
 * 3|DEFAULT: 172.23456  |
 *  \--------------------/
 *  
 */

MenuConfig::MenuConfig() {
}

enum menu_config_pos_t {
  MENU_CONFIG_POS_ITEM = 0, // scroll through items
  MENU_CONFIG_POS_MOD, // modify value
};

void MenuConfig::Input(input_type_t type, int32_t arg) {
  (void) type;
  (void) arg;
  switch (type) {
    case INPUT_TYPE_MENU:
      if (arg == INPUT_EVENT_DOWN) {
        NextMenu();
        return;
      }
      break;
    case INPUT_TYPE_ENCODER:
      switch (pos) {
        case MENU_CONFIG_POS_ITEM:
          item += (arg>0?1:-1)*arg*arg; // acceleration
          if (item >= NV_PARAM_MAX) item = NV_PARAM_MAX-1;
          if (item < 0) item = 0;
          break;
        case MENU_CONFIG_POS_MOD:
          NVParam[item] += arg;
          break;
      }
      break;
    case INPUT_TYPE_CLICK:
      if (arg == INPUT_EVENT_DOWN) {
        switch (pos) {
          case MENU_CONFIG_POS_ITEM:
            pos = MENU_CONFIG_POS_MOD;
            break;
          case MENU_CONFIG_POS_MOD:
            // TODO save NV
            pos = MENU_CONFIG_POS_ITEM;
            break;
        }
      }
      break;
    default:
      break;
  }
  need_redraw = true;
}

#define FIX(param, factor)    (param>=0)?"+":"-",abs_i32(param)/factor,abs_i32(param)%factor

void MenuConfig::Redraw() {

  LCD_ClearBuffer();

  sprintf((char*)&lcd_buf[0*LCD_XMAX],
      "CONFIG ITEM #%03ld",
      item);

  sprintf((char*)&lcd_buf[1*LCD_XMAX],
      "%s",
      NVInfo[item].name);

  switch (NVInfo[item].type) {
    case NV_TYPE_NONE:
      break;
    case NV_TYPE_BOOL:
      sprintf((char*)&lcd_buf[2*LCD_XMAX], "      %s", NVParam[item]?"ON":"OFF");
      sprintf((char*)&lcd_buf[3*LCD_XMAX], "Default:  %s", NVInfo[item].def?"ON":"OFF");
      break;
    case NV_TYPE_INT:
      sprintf((char*)&lcd_buf[2*LCD_XMAX], "%9ld", NVParam[item]);
      sprintf((char*)&lcd_buf[3*LCD_XMAX], "Default:  %9ld", NVInfo[item].def);
      break;
    case NV_TYPE_FIX10:
      sprintf((char*)&lcd_buf[2*LCD_XMAX], "%s%6ld.%01ld %s", FIX(NVParam[item],10), NVInfo[item].unit);
      sprintf((char*)&lcd_buf[3*LCD_XMAX], "Default:  %s%6ld.%01ld", FIX(NVInfo[item].def,10));
      break;
    case NV_TYPE_FIX100:
      sprintf((char*)&lcd_buf[2*LCD_XMAX], "%s%5ld.%02ld %s", FIX(NVParam[item],100), NVInfo[item].unit);
      sprintf((char*)&lcd_buf[3*LCD_XMAX], "Default:  %s%5ld.%02ld", FIX(NVInfo[item].def,100));
      break;
    case NV_TYPE_FIX1000:
      sprintf((char*)&lcd_buf[2*LCD_XMAX], "%s%4ld.%03ld %s", FIX(NVParam[item],1000), NVInfo[item].unit);
      sprintf((char*)&lcd_buf[3*LCD_XMAX], "Default:  %s%4ld.%03ld", FIX(NVInfo[item].def,1000));
      break;
  }

  /* indicate position in menu using cursor */ 
  switch (pos) {
    case MENU_CONFIG_POS_ITEM:
      LCD_SetCursor(15,0);
      break;
    case MENU_CONFIG_POS_MOD:
      LCD_SetCursor(8,2);
      break;
  }

  LCD_Redraw();
  need_redraw = false;
}





/***
 * initialize menus
 ***/
void Menu_Init() {
  g_pMenuMain = new MenuMain();
  g_pMenuHist = new MenuHist();
  g_pMenuConfig = new MenuConfig();
  g_pCurrentMenu = g_pMenuMain;
}


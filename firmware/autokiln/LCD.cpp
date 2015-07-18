#include"hal.h"
#include"ch.h"
#include"LCD.h"
#include"Os.h"

uint8_t lcd_buf[LCD_XMAX*LCD_YMAX*LCD_NUM_BUF];

uint8_t lcd_buf_select;

void LCD_Nybble() {
  //enable pulse width  >= 300ns
  //Clock enable: falling edge
  for (int i=0; i<300; i++) {
    setPin(PPIN_LCD_E);
  }
  clearPin(PPIN_LCD_E);
}

void LCD_SetPort(uint8_t i) {
  if (i & (1<<4)) {
    setPin(PPIN_LCD_DB4);
  } else {
    clearPin(PPIN_LCD_DB4);
  }
  if (i & (1<<5)) {
    setPin(PPIN_LCD_DB5);
  } else {
    clearPin(PPIN_LCD_DB5);
  }
  if (i & (1<<6)) {
    setPin(PPIN_LCD_DB6);
  } else {
    clearPin(PPIN_LCD_DB6);
  }
  if (i & (1<<7)) {
    setPin(PPIN_LCD_DB7);
  } else {
    clearPin(PPIN_LCD_DB7);
  }
}

void LCD_Command(uint8_t i)
{
  LCD_SetPort(i);
  clearPin(PPIN_LCD_RS); /* command */
  clearPin(PPIN_LCD_RW); /* write */
  LCD_Nybble(); 
  i = i<<4; 
  LCD_SetPort(i);
  LCD_Nybble();
} 

void LCD_Write(uint8_t i)
{
  LCD_SetPort(i);
  setPin(PPIN_LCD_RS); /* data */
  clearPin(PPIN_LCD_RW); /* write */
  LCD_Nybble(); 
  i = i<<4; 
  LCD_SetPort(i);
  LCD_Nybble(); 
}

void LCD_OutDir() {
  modePin(PPIN_LCD_DB4,PAL_MODE_OUTPUT_PUSHPULL);
  modePin(PPIN_LCD_DB5,PAL_MODE_OUTPUT_PUSHPULL);
  modePin(PPIN_LCD_DB6,PAL_MODE_OUTPUT_PUSHPULL);
  modePin(PPIN_LCD_DB7,PAL_MODE_OUTPUT_PUSHPULL);
}

void LCD_Timer(void * dummy) {
  dummy = dummy;
  LCD_Redraw();
}

/***
 * PUBLIC METHODS
 ***/

#define LCD_BACKLIGHT_MAX 0x1000
uint32_t lcd_bright = 0;
uint32_t lcd_bright_target = LCD_BACKLIGHT_MAX;
#define LCD_BRIGHT_STEP_UP    0x100
#define LCD_BRIGHT_STEP_DOWN  0x08

void LCD_Backlight_Init() {
  // setup PWM output

  /* configure timer */
  rccEnableAPB2(RCC_APB2ENR_TIM15EN, false);
  TIM15->PSC = 0x0024; /* 1us ticks */
  TIM15->ARR = LCD_BACKLIGHT_MAX;
  TIM15->CCR2 = 0;
  TIM15->CR1 = TIM_CR1_CEN;
  TIM15->CCMR1 = (TIM15->CCMR1 & ~TIM_CCMR1_OC2M) | (TIM_CCMR1_OC2M_1 | TIM_CCMR1_OC2M_2);
  TIM15->CCMR1 |= TIM_CCMR1_OC2PE;
  TIM15->CR1 |= TIM_CR1_ARPE;
  TIM15->CCER |= TIM_CCER_CC2E;
  TIM15->BDTR |= TIM_BDTR_MOE;
  TIM15->CR1 |= TIM_CR1_CMS_0 | TIM_CR1_CEN;
  TIM15->EGR |= TIM_EGR_UG;

  palSetPadMode(GPIOA,3,PAL_MODE_ALTERNATE(0));

}

static int32_t lcd_backlight_timer = 0;

#define LCD_BACKLIGHT_WAKETIME 10000 // ticks (~5ms)
#define LCD_BACKLIGHT_WARNTIME 2000 // ticks

void LCD_Backlight_Wake() {
  lcd_bright_target = LCD_BACKLIGHT_MAX;
  lcd_backlight_timer = LCD_BACKLIGHT_WAKETIME;
}

void LCD_Backlight_Tick() {
  /* put backlight to sleep after a time */
  if (lcd_backlight_timer > 0) {
    lcd_backlight_timer--;
    if (lcd_backlight_timer == LCD_BACKLIGHT_WARNTIME) {
      lcd_bright_target = LCD_BACKLIGHT_MAX/2;
    }
    if (lcd_backlight_timer == 0) {
      lcd_bright_target = 0;
    }
  }

  /* move brightness towards target */
  if (lcd_bright_target > lcd_bright) {
    lcd_bright += LCD_BRIGHT_STEP_UP;
    if (lcd_bright > lcd_bright_target) lcd_bright = lcd_bright_target;
    LCD_Backlight_Set(lcd_bright);
  }
  else if (lcd_bright_target < lcd_bright) {
    lcd_bright -= LCD_BRIGHT_STEP_DOWN;
    if (lcd_bright < lcd_bright_target) lcd_bright = lcd_bright_target;
    LCD_Backlight_Set(lcd_bright);
  }
}

void LCD_Backlight_Set(uint16_t brightness) {
  TIM15->CCR2 = brightness;
  TIM15->EGR |= TIM_EGR_UG;
}

void LCD_Init() {
  LCD_Backlight_Init();
  LCD_Backlight_Set(0xFFFF);

  OsZero((void*) LCD_GetBuf(),LCD_XMAX*LCD_YMAX);
  LCD_OutDir();
  clearPin(PPIN_LCD_RS);
  clearPin(PPIN_LCD_RW);
  LCD_SetPort(0x00);
  OsSleepMs(100);
  LCD_SetPort(0x30);
  OsSleepMs(30);
  LCD_Nybble();
  OsSleepMs(10);
  LCD_Nybble();
  OsSleepMs(10);
  LCD_Nybble();
  OsSleepMs(10);
  LCD_SetPort(0x20);
  LCD_Nybble();
  LCD_Command(0x28);
  LCD_Command(0x10);
  LCD_Command(0x0F);
  LCD_Command(0x06);

  lcd_buf_select = 0;

  //OsCreateTimer(LCD_Timer,NULL,OS_TIMER_PERIODIC,100);
}

uint8_t * LCD_GetBuf() 
{
  return (lcd_buf_select==0)?lcd_buf:&lcd_buf[LCD_XMAX*LCD_YMAX];
}

#define LCD_CMD_CLEAR   0x01
#define LCD_CMD_HOME    0x02

int LCD_GetIndex(int x, int y) {
  return (((2*y)%4) + y/2)*LCD_XMAX + x;
}

static int32_t lcd_cursor_x = 0;
static int32_t lcd_cursor_y = 0;

void LCD_SetCursor(int32_t x, int32_t y) {
  if (x>=0 && x<LCD_XMAX && y>=0 && y<LCD_YMAX) {
    LCD_Command(0x80 | (x + ((2*y%4) + y/2)*LCD_XMAX));
    lcd_cursor_x = x;
    lcd_cursor_y = y;
  }
}

void LCD_Redraw() {
  /* flip buffers, redrawing screen */
  LCD_Command(LCD_CMD_HOME);
  uint8_t * buf = LCD_GetBuf();
  int i;
  for (int y = 0; y<LCD_YMAX; y++) {
    for (int x = 0; x<LCD_XMAX; x++) {
      i = LCD_GetIndex(x,y);
      uint8_t c = buf[i];
      if (c >= ' ' && c <= '}') {
        c = c;
      } else {
        c = ' ';
      }
      LCD_Write(c);
    }
  }
  // restore saved cursor position
  LCD_SetCursor(lcd_cursor_x,lcd_cursor_y);
}

void LCD_ClearBuffer() {
  OsZero((void*)LCD_GetBuf(), LCD_XMAX*LCD_YMAX);
}

void LCD_Test() {
  uint8_t c = ' ';
  uint8_t * buf;
  while (true) {
    LCD_Redraw();
    OsSleepMs(200);
    if (++c>'}') c=' ';
    buf = LCD_GetBuf();
    for (int i = 0; i<LCD_XMAX*LCD_YMAX; i++) {
      buf[i] = c;
    }
  }
}


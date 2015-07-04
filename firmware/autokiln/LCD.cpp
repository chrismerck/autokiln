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

void LCD_Init() {
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

void LCD_Redraw() {
  /* flip buffers, redrawing screen */
  LCD_Command(LCD_CMD_HOME);
  uint8_t * buf = LCD_GetBuf();
  for (int i = 0; i<LCD_XMAX*LCD_YMAX; i++) {
    uint8_t c = buf[i];
    if (c >= ' ' && c <= '}') {
      c = c;
    } else {
      c = ' ';
    }
    LCD_Write(c);
  }
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



#define LCD_XMAX 20
#define LCD_YMAX 4

#define LCD_NUM_BUF 1

extern uint8_t lcd_buf[LCD_XMAX*LCD_YMAX*LCD_NUM_BUF];

void LCD_Init();
uint8_t * LCD_GetBuf();
void LCD_Redraw();
void LCD_Test();


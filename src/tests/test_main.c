#include "LCD_Driver.h"
#include "LCD_Touch.h"
#include "LCD_GUI.h"
#include "LCD_Bmp.h"
#include "DEV_Config.h"
#include "hardware/watchdog.h"
#include "pico/stdlib.h"

#include "awtk.h"
#include "lcd/lcd_mem_fragment.h"

#define LCD_W 320
#define LCD_H 480

static ret_t hardware_prepare(void) {
  System_Init();
  SD_Init();
  LCD_SCAN_DIR  lcd_scan_dir = SCAN_DIR_DFT;
  LCD_Init(lcd_scan_dir, 800);
  TP_Init(lcd_scan_dir);
  Driver_Delay_ms(1000);
  Driver_Delay_ms(2000);
  TP_GetAdFac();
  TP_Dialog(lcd_scan_dir);
  LCD_Clear(WHITE);

  return RET_OK;
}

static void lcd_test(lcd_t* lcd) {
  dirty_rects_t dirty_rects;
  memset(&dirty_rects, 0x00, sizeof(dirty_rects));
  dirty_rects.nr = 1;
  dirty_rects.max.x = 0;
  dirty_rects.max.y = 0;
  dirty_rects.max.w = 100;
  dirty_rects.max.h = 100;

  color_t COLOR_RED = color_init(0xff, 0, 0, 0xff);
  color_t COLOR_GREEN = color_init(0, 0xff, 0, 0xff);
  color_t COLOR_BLUE = color_init(0, 0, 0xff, 0xff);

  lcd_begin_frame(lcd, &dirty_rects, LCD_DRAW_NORMAL);
  lcd_set_fill_color(lcd, COLOR_RED); 
  lcd_fill_rect(lcd, 0, 0, 10, 10); 
  
  lcd_set_fill_color(lcd, COLOR_GREEN); 
  lcd_fill_rect(lcd, 10, 10, 10, 10); 
  
  lcd_set_fill_color(lcd, COLOR_BLUE); 
  lcd_fill_rect(lcd, 20, 20, 10, 10); 

  lcd_end_frame(lcd);
}

static void system_test(void) {
  lcd_t* lcd = lcd_mem_fragment_create(LCD_W, LCD_H);

  while(1){
    lcd_test(lcd);
  }

  lcd_destroy(lcd);
}

static void gui_test(void) {
  GUI_DrawRectangle(0, 0, 10, 10, RED, DRAW_FULL, LINE_SOLID);
  GUI_DrawRectangle(10, 10, 20, 20, GREEN, DRAW_FULL, LINE_SOLID);
  GUI_DrawRectangle(20, 20, 30, 30, BLUE, DRAW_FULL, LINE_SOLID);
}

extern int gui_app_start(int lcd_w, int lcd_h);

int main() {
  hardware_prepare();
  platform_prepare();

  gui_test();
}

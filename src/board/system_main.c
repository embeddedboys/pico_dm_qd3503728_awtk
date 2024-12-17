#include "LCD_Driver.h"
#include "LCD_Touch.h"
#include "LCD_GUI.h"
#include "LCD_Bmp.h"
#include "DEV_Config.h"
#include "hardware/watchdog.h"
#include "pico/stdlib.h"

#include "awtk.h"

#define LCD_W 320
#define LCD_H 480

extern int gui_app_start(int lcd_w, int lcd_h);

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
//  TP_Adjust();

  return RET_OK;
}

int main() {
  hardware_prepare();
  platform_prepare();

  gui_app_start(LCD_W, LCD_H);

  LCD_Clear(BLACK);

  return 0;
}

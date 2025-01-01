/**
 * File:   lcd_stm32_raw.c
 * Author: AWTK Develop Team
 * Brief:  stm32_raw implemented lcd interface
 *
 * Copyright (c) 2018 - 2025 Guangzhou ZHIYUAN Electronics Co.,Ltd.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * License file for more details.
 *
 */

/**
 * History:
 * ================================================================
 * 2018-02-16 Li XianJing <xianjimli@hotmail.com> created
 *
 */

#include "LCD_Driver.h"
#include "tkc/mem.h"
#include "lcd/lcd_mem_fragment.h"

#define ALLOC_BUFF_WITH_MALLOC 1

typedef uint16_t pixel_t;

#define LCD_FORMAT BITMAP_FMT_BGR565
#define pixel_from_rgb(r, g, b)                                                \
  ((((r) >> 3) << 11) | (((g) >> 2) << 5) | ((b) >> 3))
#define pixel_from_rgba(r, g, b, a)                                            \
  ((((r) >> 3) << 11) | (((g) >> 2) << 5) | ((b) >> 3))
#define pixel_to_rgba(p)                                                       \
  { (0xff & ((p >> 11) << 3)), (0xff & ((p >> 5) << 2)), (0xff & (p << 3)), 0xff }

static ret_t lcd_pico_update(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t* p) {
  int n = w * h;
  LCD_SetWindow(x, y, x + w, y + h);

  DEV_Digital_Write(LCD_DC_PIN,1);
  DEV_Digital_Write(LCD_CS_PIN,0);
  while(n--) {
    uint16_t v = *p++;
    SPI4W_Write_Byte(v >> 8);
    SPI4W_Write_Byte(v & 0XFF);
  }
  DEV_Digital_Write(LCD_CS_PIN,1);

  return RET_OK;
}

#define lcd_draw_bitmap_impl lcd_pico_update

#include "base/pixel.h"
#include "blend/pixel_ops.inc"
#include "lcd/lcd_mem_fragment.inc"

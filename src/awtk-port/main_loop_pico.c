/**
 * File:   main_loop_stm32_raw.c
 * Author: AWTK Develop Team
 * Brief:  main loop for stm32
 *
 * Copyright (c) 2018 - 2025 Guangzhou ZHIYUAN Electronics Co.,Ltd.
 *
 * this program is distributed in the hope that it will be useful,
 * but without any warranty; without even the implied warranty of
 * merchantability or fitness for a particular purpose.  see the
 * license file for more details.
 *
 */

/**
 * history:
 * ================================================================
 * 2018-02-17 li xianjing <xianjimli@hotmail.com> created
 *
 */

#include "base/idle.h"
#include "base/timer.h"
#include "tkc/platform.h"
#include "base/main_loop.h"
#include "base/event_queue.h"
#include "base/font_manager.h"
#include "lcd/lcd_mem_fragment.h"
#include "main_loop/main_loop_simple.h"

#include "ft6236.h"

ret_t platform_disaptch_input(main_loop_t* l) {
  int x = 0;
  int y = 0;

  x = ft6236_read_x();
  y = ft6236_read_y();

  if (ft6236_is_pressed()) {
    main_loop_post_pointer_event(main_loop(), TRUE, x, y);
  } else {
    main_loop_post_pointer_event(main_loop(), FALSE, x, y);
  }

  return RET_OK;
}

static lcd_t* platform_create_lcd(wh_t w, wh_t h) {
  return lcd_mem_fragment_create(w, h);
}

#include "main_loop/main_loop_raw.inc"

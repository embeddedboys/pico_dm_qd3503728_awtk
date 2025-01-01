/**
 * File:   platform.c
 * Author: AWTK Develop Team
 * Brief:  platform dependent function of stm32
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

#include "tkc/mem.h"
#include "pico/time.h"
#include "base/timer.h"

ret_t platform_prepare(void) {
  return RET_OK;
}

uint64_t get_time_ms64(void) {
  return to_ms_since_boot(get_absolute_time());
}

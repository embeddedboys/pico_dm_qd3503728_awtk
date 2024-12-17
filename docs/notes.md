# AWTK 在树莓派 pico 上的移植笔记

## 1. 配置文件 (awtk_config.h)

pico 和 stm32f103 的配置差不多，虽然 pico 的内存要大不少，但是也不足提供一个完整的 FrameBuffer，所以只能使用片段 LCD。

我们在 [awtk-stm32f103 的配置](https://github.com/zlgopen/awtk-stm32f103ze-raw/blob/master/awtk-port/awtk_config.h) 基础稍作修改即可。

```c
 /* 使用片段 LCD */
 #define FRAGMENT_FRAME_BUFFER_SIZE 40 * 1024

 /* pico 提供了一个 sleep_us 的函数的函数 */
 #define HAS_SLEEP_US64 1
```

## 2. LCD 的实现

为了提高刷新的效率，我们实现一个 lcd_draw_bitmap_impl 函数，这样可以调用更底层的函数。

```c
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
```
> 这里其实还可以进一步优化，调用 spi_write_blocking 函数，直接写入整个数组，减少函数调用的开销，不过字节顺序可能需要调整。

## 3. 触摸屏的实现

SDK 提供了一个触摸屏的驱动，但是里面并没有合适的函数来读取触摸屏的数据，所以我们需要自己实现一个 TP_Read，调用 TP_Read 读取坐标，分发到 AWTK 主循环。

```c
ret_t platform_disaptch_input(main_loop_t* l) {
  int x = 0;
  int y = 0;
  int pressed = 0;
  TP_Read(&x, &y, &pressed);
  
  if (pressed) {
    main_loop_post_pointer_event(main_loop(), TRUE, x, y); 
  } else {
    main_loop_post_pointer_event(main_loop(), FALSE, x, y); 
  }

  return RET_OK;
}

static lcd_t* platform_create_lcd(wh_t w, wh_t h) {
  return lcd_mem_fragment_create(w, h); 
}
```

## 4. 平台函数

平台函数只需要实现 `get_time_ms64` 即可。

```c
uint64_t get_time_ms64(void) {
  return to_ms_since_boot(get_absolute_time());
}
```

## 5. 编译脚本

pico 使用 cmake 编译，我们需要在 CMakeLists.txt 中添加 AWTK 的源码和头文件。 awtk_mobile_common.mk 本来是给 Android/iOS/HarmonyOS/Web 用的，在这里也可以直接使用，省去不少功夫。

```sh
include(awtk/scripts/awtk_mobile_common.mk)
include_directories(${AWTK_COMMON_INCLUDES})

set(AWTK_FLAGS " -DHAS_AWTK_CONFIG ")
set(CMAKE_C_FLAGS "${AWTK_FLAGS} ${CMAKE_C_FLAGS}")
set(CMAKE_CXX_FLAGS "${AWTK_FLAGS} ${CMAKE_CXX_FLAGS}")

add_library(awtk
  ${AWTK_BASE_SOURCE_FILES}
  ${AWTK_RAW_COMMON_SOURCE_FILES}
  ${AWTK_PORT_SOURCE_FILES}
  ${AWTK_PORT_RAW_SOURCE_FILES}
  )
```

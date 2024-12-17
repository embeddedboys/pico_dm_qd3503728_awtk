# AWTK 在树莓派 pico 上的移植笔记

## 1. 配置文件 (awtk_config.h)

pico 和 stm32f103 的配置差不多，虽然内存要大不少，但是也不足提供一个完整的 FrameBuffer，所以只能使用片段 LCD。

我们在 [awtk-stm32f103 的配置](https://github.com/zlgopen/awtk-stm32f103ze-raw/blob/master/awtk-port/awtk_config.h)基础稍作修改即可。

```c
 /* 使用片段 LCD */
 #define FRAGMENT_FRAME_BUFFER_SIZE 40 * 1024

 /* pico提供了一个 sleep_us的函数的函数 */
 #define HAS_SLEEP_US64 1
```

## 2. LCD 的实现

```sh
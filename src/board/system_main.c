#include "pico/time.h"
#include "pico/stdio.h"
#include "pico/stdlib.h"
#include "pico/stdio_uart.h"

#include "hardware/watchdog.h"
#include "hardware/pll.h"
#include "hardware/vreg.h"
#include "hardware/clocks.h"
#include "hardware/timer.h"

#include "ili9488.h"
#include "ft6236.h"
#include "backlight.h"

#include "awtk.h"

#define LCD_W LCD_HOR_RES
#define LCD_H LCD_VER_RES

extern int gui_app_start(int lcd_w, int lcd_h);

static ret_t hardware_prepare(void)
{
        /* NOTE: DO NOT MODIFY THIS BLOCK */
#define CPU_SPEED_MHZ (DEFAULT_SYS_CLK_KHZ / 1000)

        if(CPU_SPEED_MHZ > 266 && CPU_SPEED_MHZ <= 360)
                vreg_set_voltage(VREG_VOLTAGE_1_20);
        else if (CPU_SPEED_MHZ > 360 && CPU_SPEED_MHZ <= 396)
                vreg_set_voltage(VREG_VOLTAGE_1_25);
        else if (CPU_SPEED_MHZ > 396)
                vreg_set_voltage(VREG_VOLTAGE_MAX);
        else
                vreg_set_voltage(VREG_VOLTAGE_DEFAULT);

        set_sys_clock_khz(CPU_SPEED_MHZ * 1000, true);
        clock_configure(clk_peri,
                        0,
                        CLOCKS_CLK_PERI_CTRL_AUXSRC_VALUE_CLK_SYS,
                        CPU_SPEED_MHZ * MHZ,
                        CPU_SPEED_MHZ * MHZ);
        stdio_uart_init_full(uart0, 115200, 16, 17);

        ili9488_driver_init();
        ft6236_driver_init();
        backlight_driver_init();

        backlight_set_level(100);

	return RET_OK;
}

int main()
{
	hardware_prepare();
	platform_prepare();

	gui_app_start(LCD_W, LCD_H);

	return 0;
}

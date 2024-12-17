add_library(board
    config/DEV_Config.c
    lcd/LCD_Driver.c
    sdcard/MMC_SD.c
    fatfs/ff.c
    fatfs/diskio.c
    fatfs/fatfs_storage.c
    lcd/LCD_Bmp.c 
    lcd/LCD_GUI.c 
    lcd/LCD_Touch.c
    font/font8.c
    font/font16.c
    font/font24.c
    font/font12.c
    font/font20.c
    system_main.c
    )


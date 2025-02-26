# Set all global variables here
set(OVERCLOCK_ENABLED 1)    # 1: enable, 0: disable

if(OVERCLOCK_ENABLED)

    message(WARNING "Overclocking is enabled. This may damage your device. Use at own risk.")

    if(${PICO_BOARD} STREQUAL "pico" OR ${PICO_PLATFORM} STREQUAL "rp2040")
        # Overclocking profiles
        #      SYS_CLK  | FLASH_CLK | Voltage
        #  1  | 240MHz  |  120MHZ   |  1.10(V) (default, stable, recommended for most devices)
        #  2  | 266MHz  |  133MHz   |  1.10(V)
        #  3  | 360MHz  |  90MHz    |  1.20(V)
        #  4  | 400MHz  |  100MHz   |  1.30(V)
        #  5  | 416MHz  |  104MHz   |  1.30(V)
        set(OVERCLOCK_PROFILE 1)

        if(OVERCLOCK_PROFILE EQUAL 1)
            set(SYS_CLK_KHZ 240000)             # CPU clock speed
            set(PERI_CLK_KHZ ${SYS_CLK_KHZ})    # Peripheral clock speed
        elseif(OVERCLOCK_PROFILE EQUAL 2)
            set(SYS_CLK_KHZ 266000)
            set(PERI_CLK_KHZ ${SYS_CLK_KHZ})
        elseif(OVERCLOCK_PROFILE EQUAL 3)
            set(SYS_CLK_KHZ 360000)
            set(PERI_CLK_KHZ ${SYS_CLK_KHZ})
        elseif(OVERCLOCK_PROFILE EQUAL 4)
            set(SYS_CLK_KHZ 400000)
            set(PERI_CLK_KHZ ${SYS_CLK_KHZ})
        elseif(OVERCLOCK_PROFILE EQUAL 5)
            set(SYS_CLK_KHZ 416000)
            set(PERI_CLK_KHZ ${SYS_CLK_KHZ})
        else()
            message(FATAL_ERROR "Invalid overclocking profile")
        endif()
    elseif(${PICO_BOARD} STREQUAL "pico2" OR ${PICO_PLATFORM} STREQUAL "rp2350")
        # Overclocking profiles
        #      SYS_CLK  | FLASH_CLK | Voltage
        #  1  | 366MHz  |  122MHz   |  1.20(V)
        #  1  | 384MHz  |  128MHz   |  1.20(V)
        set(OVERCLOCK_PROFILE 1)

        if(OVERCLOCK_PROFILE EQUAL 1)
            set(SYS_CLK_KHZ 366000)             # CPU clock speed
            set(PERI_CLK_KHZ ${SYS_CLK_KHZ})    # Peripheral clock speed
        elseif(OVERCLOCK_PROFILE EQUAL 2)
            set(SYS_CLK_KHZ 384000)             # CPU clock speed
            set(PERI_CLK_KHZ ${SYS_CLK_KHZ})    # Peripheral clock speed
        else()
            message(FATAL_ERROR "Invalid overclocking profile")
        endif()
    endif()

else()  # OVERCLOCK_ENABLED
    message(WARNING "Overclocking is disabled.")

    if(${PICO_BOARD} STREQUAL "pico" OR ${PICO_PLATFORM} STREQUAL "rp2040")
        set(SYS_CLK_KHZ 125000) # CPU clock speed
        set(PERI_CLK_KHZ ${SYS_CLK_KHZ})    # Peripheral clock speed
    elseif(${PICO_BOARD} STREQUAL "pico2" OR ${PICO_PLATFORM} STREQUAL "rp2350")
        set(SYS_CLK_KHZ 150000) # CPU clock speed
        set(PERI_CLK_KHZ ${SYS_CLK_KHZ})    # Peripheral clock speed
    endif()

endif() # OVERCLOCK_ENABLED

# LCD Pins for 8080 interface
set(LCD_PIN_DB_BASE  0)  # 8080 LCD data bus base pin
set(LCD_PIN_DB_COUNT 16) # 8080 LCD data bus pin count
set(LCD_PIN_CS  18)  # 8080 LCD chip select pin
set(LCD_PIN_WR  19)  # 8080 LCD write pin
set(LCD_PIN_RS  20)  # 8080 LCD register select pin
set(LCD_PIN_RST 22)  # 8080 LCD reset pin
set(LCD_PIN_BL  28)  # 8080 LCD backlight pin
set(LCD_HOR_RES 480)
set(LCD_VER_RES 320)
set(DISP_OVER_PIO 1) # 1: PIO, 0: GPIO
set(PIO_USE_DMA   1)   # 1: use DMA, 0: not use DMA
if(OVERCLOCK_ENABLED)
    set(I80_BUS_WR_CLK_KHZ 58000)
else()
    set(I80_BUS_WR_CLK_KHZ 50000)
endif()

# Rotation configuration
set(LCD_ROTATION 0)  # 0: normal, 1: 90 degree, 2: 180 degree, 3: 270 degree
if(${LCD_ROTATION} EQUAL 0 OR ${LCD_ROTATION} EQUAL 2)
    set(LCD_HOR_RES 320)
    set(LCD_VER_RES 480)
elseif(${LCD_ROTATION} EQUAL 1 OR ${LCD_ROTATION} EQUAL 3)
    set(LCD_HOR_RES 480)
    set(LCD_VER_RES 320)
else()
    message(FATAL_ERROR "ERROR: Invalid Display rotation")
endif()

# include PIO library here
add_subdirectory(pio)
target_compile_definitions(pio_i80 PRIVATE LCD_PIN_RS=${LCD_PIN_RS})
target_compile_definitions(pio_i80 PRIVATE LCD_PIN_CS=${LCD_PIN_CS})
target_compile_definitions(pio_i80 PRIVATE DEFAULT_PIO_CLK_KHZ=${PERI_CLK_KHZ})
target_compile_definitions(pio_i80 PRIVATE PIO_USE_DMA=${PIO_USE_DMA})
target_compile_definitions(pio_i80 PRIVATE I80_BUS_WR_CLK_KHZ=${I80_BUS_WR_CLK_KHZ})


add_library(board
    lcd/backlight.c
    lcd/ft6236.c
    lcd/ili9488.c
    system_main.c
)
target_link_libraries(board PUBLIC pio_i80 hardware_i2c hardware_pwm)
target_include_directories(board PUBLIC lcd/)

# add target common defines here
target_compile_definitions(board PRIVATE DEFAULT_SYS_CLK_KHZ=${SYS_CLK_KHZ})
target_compile_definitions(board PRIVATE DEFAULT_PERI_CLK_KHZ=${PERI_CLK_KHZ})
target_compile_definitions(board PRIVATE LCD_PIN_DB_BASE=${LCD_PIN_DB_BASE})
target_compile_definitions(board PRIVATE LCD_PIN_DB_COUNT=${LCD_PIN_DB_COUNT})
target_compile_definitions(board PRIVATE LCD_PIN_CS=${LCD_PIN_CS})
target_compile_definitions(board PRIVATE LCD_PIN_WR=${LCD_PIN_WR})
target_compile_definitions(board PRIVATE LCD_PIN_RS=${LCD_PIN_RS})
target_compile_definitions(board PRIVATE LCD_PIN_RST=${LCD_PIN_RST})
target_compile_definitions(board PRIVATE LCD_PIN_BL=${LCD_PIN_BL})
target_compile_definitions(board PRIVATE LCD_ROTATION=${LCD_ROTATION})
target_compile_definitions(board PRIVATE LCD_HOR_RES=${LCD_HOR_RES})
target_compile_definitions(board PRIVATE LCD_VER_RES=${LCD_VER_RES})
target_compile_definitions(board PRIVATE DISP_OVER_PIO=${DISP_OVER_PIO})

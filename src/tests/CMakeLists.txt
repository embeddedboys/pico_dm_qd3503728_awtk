
file(GLOB APP_SOURCE_FILES 
  *.c
  common/*.c
  pages/*.c
)

add_executable(app ${APP_SOURCE_FILES})

# pull in common dependencies
target_link_libraries(app awtk board pico_stdlib hardware_uart hardware_spi)

# create map/bin/hex file etc.
pico_add_extra_outputs(app)


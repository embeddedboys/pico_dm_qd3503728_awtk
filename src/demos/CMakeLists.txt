file(GLOB APP_SOURCE_FILES
  hello/src/*.c
  hello/src/common/*.c
  hello/src/pages/*.c
)

add_executable(${PROJECT_NAME} ${APP_SOURCE_FILES})

# pull in common dependencies
target_link_libraries(${PROJECT_NAME} awtk board pico_stdlib hardware_uart)

# create map/bin/hex file etc.
pico_add_extra_outputs(${PROJECT_NAME})


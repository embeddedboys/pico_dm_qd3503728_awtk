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

target_compile_definitions(awtk PRIVATE
  MINIZ_NO_TIME
)

add_subdirectory(board)
add_subdirectory(demos)
#add_subdirectory(tests)

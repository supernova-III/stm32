FetchContent_Declare(ff16
  URL https://elm-chan.org/fsw/ff/arc/ff16.zip
)

FetchContent_GetProperties(ff16)
if (NOT ff16_POPULATED)
  FetchContent_Populate(ff16)
endif()

set(CMSIS_PATH ${stm32_cmsis_SOURCE_DIR})
set(CMSIS6_PATH ${arm_cmsis_6_SOURCE_DIR})

add_executable(${PROJECT_NAME}_test main.cpp)

add_library(${PROJECT_NAME}_startup_lib STATIC
   startup.cpp)

target_link_libraries(${PROJECT_NAME}_test ${PROJECT_NAME}_startup_lib)

target_compile_definitions(${PROJECT_NAME}_startup_lib
  PUBLIC
  -DSTM32F411xE)



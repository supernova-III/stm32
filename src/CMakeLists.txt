FetchContent_Declare(stm32_cmsis
  GIT_REPOSITORY https://github.com/STMicroelectronics/cmsis-device-f4.git
  GIT_TAG v2.6.11
)

FetchContent_Declare(arm_cmsis_6
  GIT_REPOSITORY https://github.com/ARM-software/CMSIS_6.git
  GIT_TAG v6.2.0
)

FetchContent_Declare(ff16
  URL https://elm-chan.org/fsw/ff/arc/ff16.zip
)

FetchContent_GetProperties(stm32_cmsis)
if (NOT stm32_cmsis_POPULATED)
  FetchContent_Populate(stm32_cmsis)
endif()

FetchContent_GetProperties(arm_cmsis_6)
if (NOT arm_cmsis_6_POPULATED)
  FetchContent_Populate(arm_cmsis_6)
endif()

FetchContent_GetProperties(ff16)
if (NOT ff16_POPULATED)
  FetchContent_Populate(ff16)
endif()

set(CMSIS_PATH ${stm32_cmsis_SOURCE_DIR})
set(CMSIS6_PATH ${arm_cmsis_6_SOURCE_DIR})

add_executable(${PROJECT_NAME}_test main.cpp)

add_library(${PROJECT_NAME}_startup_lib STATIC
  cpp_runtime.c
  ${CMSIS_PATH}/Source/Templates/system_stm32f4xx.c
  ${CMSIS_PATH}/Source/Templates/gcc/startup_stm32f411xe.s)

target_include_directories(${PROJECT_NAME}_startup_lib
  PUBLIC
  ${CMSIS6_PATH}/CMSIS/Core/Include
  ${CMSIS_PATH}/Include)

target_link_libraries(${PROJECT_NAME}_test ${PROJECT_NAME}_startup_lib)

target_compile_definitions(${PROJECT_NAME}_startup_lib
  PUBLIC
  -DSTM32F411xE)



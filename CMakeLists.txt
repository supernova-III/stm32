cmake_minimum_required(VERSION 3.25)

project(fatfs_spi_driver LANGUAGES CXX ASM)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_EXPORT_COMPILE_COMMANDS On)

set(STM32CubeF4Path ${CMAKE_SOURCE_DIR}/deps/STM32CubeF4)
set(CMSISPath ${STM32CubeF4Path}/Drivers/CMSIS)

add_executable(${PROJECT_NAME}_test main.cpp)

add_library(${PROJECT_NAME}_startup_lib STATIC
  cpp_runtime.c
  ${STM32CubeF4Path}/Projects/STM32F411RE-Nucleo/Demonstrations/Src/system_stm32f4xx.c
  startup_stm32f411xe.s)
  
target_link_libraries(${PROJECT_NAME}_test ${PROJECT_NAME}_startup_lib)

target_compile_definitions(${PROJECT_NAME}_test
  PUBLIC
  -DSTM32F411xE)

target_include_directories(${PROJECT_NAME}_test
  PUBLIC
  ${CMSISPath}/Include
  ${CMSISPath}/Device/ST/STM32F4xx/Include)

cmake_minimum_required(VERSION 3.25)

project(fatfs_spi_driver LANGUAGES CXX ASM C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_EXPORT_COMPILE_COMMANDS On)

include(FetchContent)
set(FETCHCONTENT_QUIET FALSE)

add_subdirectory(libs)
add_subdirectory(drivers)
add_subdirectory(src)

cmake_minimum_required(VERSION 3.25)

project(fatfs_spi_driver LANGUAGES CXX ASM C)

option(BUILD_UNIT_TESTS "Build unit tests instead of project" OFF)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_EXPORT_COMPILE_COMMANDS On)

include(FetchContent)
set(FETCHCONTENT_QUIET FALSE)

add_subdirectory(libs)
add_subdirectory(drivers)

if (BUILD_UNIT_TESTS)
  add_subdirectory(unit_tests)
else()
  add_subdirectory(src)
endif()


add_library(unit_tests_common STATIC test_utils.cpp)
target_include_directories(unit_tests_common PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

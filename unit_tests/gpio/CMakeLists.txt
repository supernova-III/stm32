add_library(gpio OBJECT 
  gpio_output_tests.cpp
  common.cpp
)
target_link_libraries(gpio PUBLIC gtest gpio_driver_lib unit_tests_common)

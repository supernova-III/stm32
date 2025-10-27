add_library(gpio OBJECT configure_output_tests.cpp)
target_link_libraries(gpio PUBLIC gtest gpio_driver_lib)

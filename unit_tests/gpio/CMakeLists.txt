add_library(gpio OBJECT test.cpp)
target_link_libraries(gpio PUBLIC gtest gpio_driver_lib)

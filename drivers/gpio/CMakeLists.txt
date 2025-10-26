add_library(gpio_driver_lib STATIC gpio_driver.cpp)
target_include_directories(gpio_driver_lib PUBLIC .)
target_link_libraries(gpio_driver_lib PUBLIC driver_commonlib)

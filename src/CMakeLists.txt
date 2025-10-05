# FetchContent_Declare(ff16
#   URL https://elm-chan.org/fsw/ff/arc/ff16.zip
# )
# 
# FetchContent_GetProperties(ff16)
# if (NOT ff16_POPULATED)
#   FetchContent_Populate(ff16)
# endif()

add_executable(${PROJECT_NAME}_test main.cpp)

add_library(${PROJECT_NAME}_startup_lib STATIC
  startup.cpp
  delay.cpp)

target_link_libraries(${PROJECT_NAME}_test ${PROJECT_NAME}_startup_lib)


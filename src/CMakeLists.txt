# FetchContent_Declare(ff16
#   URL https://elm-chan.org/fsw/ff/arc/ff16.zip
# )
# 
# FetchContent_GetProperties(ff16)
# if (NOT ff16_POPULATED)
#   FetchContent_Populate(ff16)
# endif()

add_executable(${PROJECT_NAME}_test main.cpp
  startup.cpp
  rcc.cpp
  gpio.cpp
  delay.cpp
)



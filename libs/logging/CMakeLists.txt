FetchContent_Declare(printf
  GIT_REPOSITORY https://github.com/mpaland/printf.git
  GIT_TAG v4.0.0)

FetchContent_GetProperties(printf)
if (NOT printf_POPULATED)
  FetchContent_Populate(printf)
endif()

message(STATUS "printf.c path: ${printf_SOURCE_DIR}/printf.c")

add_library(printflib STATIC ${printf_SOURCE_DIR}/printf.c)
target_include_directories(printflib PUBLIC ${printf_SOURCE_DIR})
set_target_properties(printflib PROPERTIES LINKER_LANGUAGE C)

add_library(logging STATIC printf.cpp)
target_link_libraries(logging PUBLIC printflib)


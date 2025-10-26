FetchContent_Declare(gtest 
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG v1.17.0)

FetchContent_MakeAvailable(gtest)

add_executable(unit_tests)

add_subdirectory(gpio)

target_sources(unit_tests PRIVATE
  $<TARGET_OBJECTS:gpio>)

target_link_libraries(unit_tests PRIVATE gtest_main)


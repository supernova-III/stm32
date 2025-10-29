FetchContent_Declare(gtest 
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG v1.17.0)

FetchContent_MakeAvailable(gtest)
enable_testing()

add_subdirectory(gpio)
add_executable(unit_tests)

target_link_libraries(unit_tests PRIVATE gpio gtest_main)

include(GoogleTest)
gtest_discover_tests(unit_tests)

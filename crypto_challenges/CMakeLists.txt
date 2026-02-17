enable_testing()

add_library(
    crypto_lib INTERFACE
)

target_include_directories(
    crypto_lib INTERFACE
    ./
)

add_executable(
  01_challenges
  01_challenges_test.cpp
)
target_link_libraries(
  01_challenges
  GTest::gtest_main
  crypto_lib
)

include(GoogleTest)
gtest_discover_tests(01_challenges)

enable_testing()

add_executable(
  concurrency_test
  test_thread.cpp
)
target_link_libraries(
  concurrency_test
  GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(concurrency_test)


add_executable(concurrency_thread
    concurrency.cpp
)

add_executable(mutex
    mutex.cpp
)

add_executable(atomic
    atomic.cpp
)

add_executable(condition_variable
    condition_variable.cpp
)

add_executable(future_async
    future_async.cpp
)

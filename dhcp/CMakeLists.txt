
set(DHCP_SOURCES
    ./src/conf/conf_default.cpp
    ./src/sock/dhcp_socket.cpp
    ./src/sock/service_socket.cpp
)

set(DHCP_TESTS
    ./test/database/test_database_ram.cpp
    ./test/algo/test_naive_ip_allocator.cpp
)

set(DHCP_INCLUDE_PATHS
    ./src/
    ./src/algo/
    ./src/conf/
    ./src/time/
    ./src/logger/
    ./src/database/
    ./src/sock
)

set(DHCP_TESTS_INCLUDE_PATHS
    ./test
)

add_executable(dhcp
    ./src/main.cpp
    ${DHCP_SOURCES}
)

target_include_directories(dhcp PRIVATE
    ${DHCP_INCLUDE_PATHS}
)

target_link_libraries(dhcp PRIVATE spdlog::spdlog)
target_link_libraries(dhcp PRIVATE fmt::fmt)
target_link_libraries(dhcp PRIVATE CLI11::CLI11)

enable_testing()

add_executable(
  dhcp_test
  ${DHCP_SOURCES}
  ${DHCP_TESTS}
)

target_include_directories(dhcp_test PRIVATE
    ${DHCP_INCLUDE_PATHS}
    ${DHCP_TESTS_INCLUDE_PATHS}
)

target_link_libraries(
  dhcp_test
  GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(dhcp_test)


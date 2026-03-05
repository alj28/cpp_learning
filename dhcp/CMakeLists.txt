

add_executable(dhcp
    ./src/main.cpp
    ./src/conf/conf_default.cpp
)

target_include_directories(dhcp PRIVATE
    ./src/
    ./src/conf/
    ./src/time/
    ./src/logger/
)

target_link_libraries(dhcp PRIVATE spdlog::spdlog)
target_link_libraries(dhcp PRIVATE fmt::fmt)
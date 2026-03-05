
#include <iostream>
#include <fmt/base.h>

#include "spd_logger.hpp"
#include "time_system.hpp"

SpdLogger logger;
SystemTime tm;

int main(void)
{
    logger.info(std::string("Test"));

    std::uint32_t now = tm.now();
    logger.info(fmt::format("Epoch: {}", now));
    return -1;
}
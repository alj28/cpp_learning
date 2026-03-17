
#include <string>
#include <iostream>
#include <fmt/base.h>

#include "spd_logger.hpp"
#include "time_system.hpp"
#include "conf_default.hpp"
#include "database_ram.hpp"
#include "dhcp_socket.hpp"
#include "service_socket.hpp"

#include <iostream>
#include <chrono>

SpdLogger logger;
DefaultConf config;
SystemTime tm;
RamDatabase db{logger};


int main(void)
{
    ServiceSocket service_socket(std::string("127.0.0.1"), 5500);
    DHCPSocket s(logger, config);
    s.start();
    std::this_thread::sleep_for(std::chrono::seconds(2));
    s.stop();
    return -1;
}
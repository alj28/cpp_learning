#ifndef _DHCP_SOCKET_HPP_
#define _DHCP_SOCKET_HPP_

#include <cstdint>
#include <thread>
#include <atomic>

#include "logger_interface.hpp"
#include "conf_interface.hpp"


class DHCPSocket
{
public:
    DHCPSocket(ILogger& logger, IConf& conf);
    virtual ~DHCPSocket();

    void start();
    void stop();

private:
    ILogger& logger;
    IConf& conf;
    std::thread thread_handle;
    std::atomic<bool> thread_running{false};

private:
    void runnable();
};


#endif


#include "dhcp_socket.hpp"

#include <netinet/in.h>
#include <sys/socket.h>

#include <iostream>
#include <chrono>

DHCPSocket::DHCPSocket(ILogger& logger, IConf& conf):
        logger{logger},
        conf{conf}
{

}

DHCPSocket::~DHCPSocket()
{
    stop();
}


void DHCPSocket::runnable()
{
    while (thread_running)
    {
        
        std::cout << "Runnable running ...." << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }
}

void DHCPSocket::start()
{
    thread_running = true;
    thread_handle = std::thread(&DHCPSocket::runnable, this);
}

void DHCPSocket::stop()
{
    thread_running = false;
    if (thread_handle.joinable())
    {
        thread_handle.join();
    }
}


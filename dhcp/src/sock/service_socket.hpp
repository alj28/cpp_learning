#pragma once

#include <cstdint>
#include <string>
#include <arpa/inet.h>

class ServiceSocket
{
public:
    ServiceSocket(std::string ip, std::uint16_t port);
    virtual ~ServiceSocket() = default;

private:
    std::string ip;
    std::uint16_t port;
    int sockfd;
};

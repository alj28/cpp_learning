
#include <stdexcept>

#include "service_socket.hpp"

ServiceSocket::ServiceSocket(std::string ip, std::uint16_t port):
    ip(ip),
    port(port)
{
    sockfd = socket(
        AF_INET,
        SOCK_STREAM,    // TCP
        0
    );
    if (0 == sockfd)
    {
        throw std::runtime_error("Cannot open a socket");
    }
}
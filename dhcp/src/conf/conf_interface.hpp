#ifndef _CONF_INTERFACE_HPP_
#define _CONF_INTERFACE_HPP_

#include <cstdint>

struct conf_addr_range
{
    std::uint32_t ip_addr_start;
    std::uint32_t ip_addr_end;
};  

struct conf_interface_port
{
    std::uint16_t listening_port;
    std::uint16_t response_port;
};

struct conf_timeouts
{
    std::uint32_t lease_timeout;
};

class IConf
{
public:
    virtual ~IConf(void) = default;

    virtual const struct conf_addr_range* getAddrRange(void) = 0;
    virtual const struct conf_interface_port* getInterfacePort(void) = 0;
    virtual const struct conf_timeouts* getTimeouts(void) = 0;
};



#endif 

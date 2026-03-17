
#include "conf_default.hpp"

static constexpr std::uint32_t IP(std::uint8_t a, std::uint8_t b, std::uint8_t c, std::uint8_t d)
{
    return (
        (a << 24)   |
        (b << 16)   |
        (c << 8)    |
        (d << 0)
    );
}


static const struct conf_addr_range default_conf_addr_range = {
    .ip_addr_start = IP(192, 168, 0, 100),
    .ip_addr_end = IP(192, 168, 0, 200)
};

const struct conf_addr_range* DefaultConf::getAddrRange(void)
{
    return &default_conf_addr_range;
}

static const struct conf_interface_port default_conf_interface_port = {
    .listening_port = 67,
    .response_port = 68
};

const struct conf_interface_port* DefaultConf::getInterfacePort(void)
{
    return &default_conf_interface_port;
}

static const struct conf_timeouts default_conf_timeouts = {
    .lease_timeout = (60*60*24)
};

const struct conf_timeouts* DefaultConf::getTimeouts(void)
{
    return &default_conf_timeouts;
}

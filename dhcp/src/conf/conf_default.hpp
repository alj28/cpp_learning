#ifndef _CONF_DEFAULT_HPP_
#define _CONF_DEFAULT_HPP_

#include "conf_interface.hpp"

class DefaultConf: public IConf
{
public:
    DefaultConf(){};
    ~DefaultConf() = default;

    const struct conf_addr_range* getAddrRange(void);
    const struct conf_interface_port* getInterfacePort(void);
    const struct conf_timeouts* getTimeouts(void);
};


#endif

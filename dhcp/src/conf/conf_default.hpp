#ifndef _CONF_DEFAULT_HPP_
#define _CONF_DEFAULT_HPP_

#include "conf_interface.hpp"

class DefaultConf: public IConf
{
public:
    ~DefaultConf(void) = default;

    const struct conf_addr_range* getAddrRange(void);
    const struct conf_interface_port* getListeningPort(void);
};


#endif

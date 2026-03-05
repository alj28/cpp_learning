#ifndef _TIME_INTERFACE_HPP_
#define _TIME_INTERFACE_HPP_

#include <cstdint>

class ITime
{
public:
    virtual ~ITime(void) = default;
    virtual std::uint32_t now(void) = 0;
};



#endif 

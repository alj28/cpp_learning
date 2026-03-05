#ifndef _TIME_SYSTEM_HPP_
#define _TIME_SYSTEM_HPP_

#include <ctime>

#include "time_interface.hpp"

class SystemTime: public ITime
{
public:
    ~SystemTime(void) = default;

    std::uint32_t now(void)
    {
        return (std::uint32_t)(std::time(nullptr));
    }
};

#endif

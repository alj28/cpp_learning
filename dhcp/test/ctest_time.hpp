#ifndef _CTEST_TIME_HPP_
#define _CTEST_TIME_HPP_

#include <cstdint>

#include "time_interface.hpp"

class CTestTime: public ITime
{
public:
    CTestTime(std::uint32_t now):
        time_now{now}
    {}
    ~CTestTime() = default;

    std::uint32_t now()
    {
        return time_now;
    }

    void set_time(std::uint32_t time)
    {
        time_now = time;
    }

private:
    std::uint32_t time_now;
};

#endif 

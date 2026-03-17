#ifndef _LOGGER_HPP_
#define _LOGGER_HPP_

#include <cstdint>
#include <iostream>

#include "logger_interface.hpp"

#define CTEST_LOGGER_EN_INFO        0x0001
#define CTEST_LOGGER_EN_WARN        0x0002
#define CTEST_LOGGER_EN_ERROR       0x0004
#define CTEST_LOGGER_EN_DEBUG       0x0008

class CTestLogger: public ILogger
{
public:
    CTestLogger(std::uint16_t en_flags):
        en_flags{en_flags}
    {}
    virtual ~CTestLogger(void) = default;

    void info(const std::string& msg)
    {
        if (CTEST_LOGGER_EN_INFO != (en_flags & CTEST_LOGGER_EN_INFO))
        {
            return;
        }
        std::cout << msg << std::endl;
    }
    void info(const char* msg)
    {
        if (CTEST_LOGGER_EN_INFO != (en_flags & CTEST_LOGGER_EN_INFO))
        {
            return;
        }
        std::cout << msg << std::endl;
    }

    void warn(const std::string& msg)
    {
        if (CTEST_LOGGER_EN_WARN != (en_flags & CTEST_LOGGER_EN_WARN))
        {
            return;
        }
        std::cout << msg << std::endl;
    }

    void warn(const char* msg)
    {
        if (CTEST_LOGGER_EN_WARN != (en_flags & CTEST_LOGGER_EN_WARN))
        {
            return;
        }
        std::cout << msg << std::endl;
    }

    void error(const std::string& msg)
    {
        if (CTEST_LOGGER_EN_ERROR != (en_flags & CTEST_LOGGER_EN_ERROR))
        {
            return;
        }
        std::cout << msg << std::endl;
    }

    void error(const char* msg)
    {
        if (CTEST_LOGGER_EN_ERROR != (en_flags & CTEST_LOGGER_EN_ERROR))
        {
            return;
        }
        std::cout << msg << std::endl;
    }

    void debug(const std::string& msg)
    {
        if (CTEST_LOGGER_EN_DEBUG != (en_flags & CTEST_LOGGER_EN_DEBUG))
        {
            return;
        }
        std::cout << msg << std::endl;
    }

    void debug(const char* msg)
    {
        if (CTEST_LOGGER_EN_DEBUG != (en_flags & CTEST_LOGGER_EN_DEBUG))
        {
            return;
        }
        std::cout << msg << std::endl;
    }

private:
    std::uint16_t en_flags;
};

#endif

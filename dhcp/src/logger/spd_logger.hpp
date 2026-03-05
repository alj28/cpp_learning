#ifndef _SPD_LOGGER_H_
#define _SPD_LOGGER_H_

#include "logger_interface.hpp"
#include "spdlog/spdlog.h"

class SpdLogger: public ILogger
{
public:
    SpdLogger(void){}

    ~SpdLogger(void) = default;

    void info(const std::string& msg)
    {
        spdlog::info(msg);
    }

    void warn(const std::string& msg)
    {
        spdlog::warn(msg);
    }

    void error(const std::string& msg)
    {
        spdlog::critical(msg);
    }

    void debug(const std::string& msg)
    {
        spdlog::debug(msg);
    }


};


#endif
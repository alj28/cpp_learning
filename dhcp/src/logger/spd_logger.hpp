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

    void info(const char* msg)
    {
        spdlog::info(std::string(msg));
    }

    void warn(const std::string& msg)
    {
        spdlog::warn(msg);
    }

    void warn(const char* msg)
    {
        spdlog::warn(std::string(msg));
    }

    void error(const std::string& msg)
    {
        spdlog::critical(msg);
    }

    void error(const char* msg)
    {
        spdlog::error(std::string(msg));
    }

    void debug(const std::string& msg)
    {
        spdlog::debug(msg);
    }

    void debug(const char* msg)
    {
        spdlog::debug(std::string(msg));
    }


};


#endif
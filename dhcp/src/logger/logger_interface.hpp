#ifndef _LOGGER_INTERFACE_
#define _LOGGER_INTERFACE_

#include <string>

class ILogger
{
public:
    virtual ~ILogger(void) = default;
    virtual void info(const std::string&) = 0;
    virtual void warn(const std::string&) = 0;
    virtual void error(const std::string&) = 0;
    virtual void debug(const std::string&) = 0;
};


#endif

#ifndef _DATABASE_INTERFACE_HPP_
#define _DATABASE_INTERFACE_HPP_

#include <cstdint>
#include <optional>

/*  TODO:
 *      -   not clear that MAC is very imporant - is a key
 *
 */

struct client_model
{
    std::uint64_t mac;
    std::uint32_t assigned_ip;
    std::uint32_t lease_timeout;
    
    bool operator==(const client_model& other) const
    {
        return (
            (mac == other.mac) &&
            (assigned_ip == other.assigned_ip) &&
            (lease_timeout == other.lease_timeout)
        );
    }
};

class IDatabase
{
public:
    virtual ~IDatabase() = default;

    virtual std::optional<struct client_model> get_client(std::uint64_t mac) = 0;
    virtual std::optional<struct client_model> get_client_by_ip(std::uint32_t ip) = 0;
    virtual void update_client(const struct client_model& client) = 0;
    virtual void remove_client_by_mac(std::uint64_t mac) = 0;
    virtual void remove_client_by_ip(std::uint32_t ip) = 0;

    virtual std::optional<std::uint32_t> get_greatest_IP() = 0;
};


#endif

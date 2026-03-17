#ifndef _DATABASE_RAM_HPP_
#define _DATABASE_RAM_HPP_

#include <mutex>
#include <unordered_map>

#include "database_interface.hpp"
#include "logger_interface.hpp"

class RamDatabase: public IDatabase
{
public:
    RamDatabase(ILogger& logger):
        logger{logger}
    {

    }

    ~RamDatabase() = default;

    std::optional<struct client_model> get_client(std::uint64_t mac)
    {
        std::lock_guard<std::mutex> lock(mutex);
        auto it = data.find(mac);
        if (it == data.end())
        {
            logger.warn("The " + std::to_string(mac) + " does not exists in the database.");
            return std::nullopt;
        }
        return std::optional<struct client_model>{it->second};
    }

    std::optional<struct client_model> get_client_by_ip(std::uint32_t ip)
    {
        std::lock_guard<std::mutex> lock(mutex);
        for (auto c : data)
        {
            if (ip == c.second.assigned_ip)
            {
                return std::optional<struct client_model>{c.second};
            }
        }
        return std::nullopt;
    }

    void update_client(const struct client_model& client)
    {
        std::lock_guard<std::mutex> lock(mutex);
        data[client.mac] = client;
        logger.info("The " + std::to_string(client.mac) + " updated in the database.");
    }

    void remove_client_by_mac(std::uint64_t mac)
    {
        std::lock_guard<std::mutex> lock(mutex);
        auto it = data.find(mac);
        if (it == data.end())
        {
            logger.warn("The " + std::to_string(mac) + " cannot be erased as it is not in the database.");
            return;
        }
        data.erase(it);
    }

    void remove_client_by_ip(std::uint32_t ip)
    {
        std::lock_guard<std::mutex> lock(mutex);
        for (auto it = data.begin(); it != data.end(); ++it)
        {
            if (ip == it->second.assigned_ip)
            {
                data.erase(it);
                return;
            }
        }
        logger.warn("The " + std::to_string(ip) + " cannot be erased as it is not in the database.");
    }

    std::optional<std::uint32_t> get_greatest_IP()
    {
        std::uint32_t greatest_IP = 0;
        for (auto& c : data)
        {
            if (c.second.assigned_ip > greatest_IP)
            {
                greatest_IP = c.second.assigned_ip;
            }
        }

        if (0 == greatest_IP)
        {
            std::nullopt;
        }
        return std::optional<std::uint32_t>{greatest_IP};
    }

private:
    ILogger& logger;

    std::mutex mutex;
    std::unordered_map<std::uint64_t, struct client_model> data;
};


#endif

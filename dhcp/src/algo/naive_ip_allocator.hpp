#ifndef _NAIVE_IP_ALLOCATOR_HPP_
#define _NAIVE_IP_ALLOCATOR_HPP_

#include <mutex>

#include "ip_allocator_interface.hpp"
#include "conf_interface.hpp"
#include "logger_interface.hpp"
#include "database_interface.hpp"
#include "time_interface.hpp"

class NaiveIPAllocator: public IIPAllocator
{
public:
    NaiveIPAllocator(IConf& conf, ILogger& logger, IDatabase& db, ITime& time):
        conf{conf},
        logger{logger},
        db{db},
        time{time}
    {
        next_free_ip = find_next_free_ip(conf.getAddrRange()->ip_addr_start);

    }
    virtual ~NaiveIPAllocator() = default;

    std::optional<std::uint32_t> assign_free_ip(std::uint64_t mac)
    {
        std::lock_guard<std::recursive_mutex> lock(mutex);
        std::optional<struct client_model> existing_client = db.get_client(mac);
        if (std::nullopt != existing_client)
        {
            logger.warn("A client with mac: " + std::to_string(mac) + " already has an IP.");
            existing_client->lease_timeout = time.now() + conf.getTimeouts()->lease_timeout;
            return existing_client->assigned_ip;
        }

        if (std::nullopt == next_free_ip)
        {
            logger.warn("IP pool is full. Cannot allocate IP for the " + std::to_string(mac));
            return std::nullopt;
        }

        next_free_ip = find_next_free_ip(*next_free_ip);
        if (std::nullopt == next_free_ip)
        {
            logger.warn("IP pool is full. Cannot allocate IP for the " + std::to_string(mac));
            return std::nullopt;
        }

        struct client_model client = {
            .mac = mac,
            .assigned_ip = *next_free_ip,
            .lease_timeout = time.now() + conf.getTimeouts()->lease_timeout,
        };
        db.update_client(client);

        return client.assigned_ip;
    }

    void refresh_lease_timeout(std::uint64_t mac)
    {
        std::lock_guard<std::recursive_mutex> lock(mutex);
        std::optional<struct client_model> client = db.get_client(mac);
        if (std::nullopt == client)
        {
            logger.error("The client with mac: " + std::to_string(mac) + " does not exists...");
            return;
        }

        client->lease_timeout = time.now() + conf.getTimeouts()->lease_timeout;
        db.update_client(*client);
    }

    void release_ip(std::uint64_t mac)
    {
        std::lock_guard<std::recursive_mutex> lock(mutex);
        std::optional<struct client_model> client = db.get_client(mac);
        if (std::nullopt == client)
        {
            logger.error("The client with mac: " + std::to_string(mac) + " does not exists. Cannot release its IP.");
            return;
        }
        db.remove_client_by_mac(mac);
        next_free_ip = std::optional<std::uint32_t>(client->assigned_ip);
    }

    void garbage_collector()
    {
        std::lock_guard<std::recursive_mutex> lock(mutex);
        std::uint32_t ip = conf.getAddrRange()->ip_addr_start;
        std::uint32_t ip_pool_size = conf.getAddrRange()->ip_addr_end - conf.getAddrRange()->ip_addr_start;
        for (std::uint32_t i = 0; i < ip_pool_size; ++i)
        {
            std::optional<struct client_model> client = db.get_client_by_ip(ip);
            ip++;
            if (std::nullopt == client)
            {
                continue;
            }

            std::uint32_t now = time.now();
            if (client->lease_timeout <= now)
            {
                logger.info("Lease time of the " + std::to_string(client->mac) + " has expired.");
                db.remove_client_by_mac(client->mac);
            }
        }


    }

private:
    IConf& conf;
    ILogger& logger;
    IDatabase& db;
    ITime& time;

    std::optional<uint32_t> next_free_ip;

    std::recursive_mutex mutex;

private:
    std::optional<std::uint32_t> find_next_free_ip(std::uint32_t start_ip)
    {
        std::uint32_t ip = start_ip;
        std::uint32_t ip_pool_size = conf.getAddrRange()->ip_addr_end - conf.getAddrRange()->ip_addr_start;
        std::uint32_t i;
        for (i = 0; i < ip_pool_size; i++)
        {
            std::optional<struct client_model> client = db.get_client_by_ip(ip);
            if (std::nullopt == client)
            {
                break;
            }
            ip++;
            if (conf.getAddrRange()->ip_addr_end <= ip)
            {
                ip = conf.getAddrRange()->ip_addr_start;
            }
        }

        if (ip_pool_size == i)
        {
            logger.warn("No free IPs in the IP pool.");
            return std::nullopt;
        }
        return std::optional<std::uint32_t>(ip);
    }
};


#endif

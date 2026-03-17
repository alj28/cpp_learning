#include <gtest/gtest.h>

#include <vector>

#include "database_ram.hpp"
#include "ctest_logger.hpp"
#include "conf_default.hpp"
#include "naive_ip_allocator.hpp"
#include "ctest_time.hpp"


TEST(NaiveIPAllocator, AssignFreeIP)
{
    CTestLogger logger{0xFFFF};
    RamDatabase db{logger};
    DefaultConf conf;
    CTestTime time{0};

    NaiveIPAllocator ip_allocator{
        conf,
        logger,
        db,
        time
    };

    std::optional<std::uint32_t> assigned_ip = ip_allocator.assign_free_ip(0x0102030405060708);
    EXPECT_TRUE(std::nullopt != assigned_ip);
    EXPECT_GE(*assigned_ip, conf.getAddrRange()->ip_addr_start);
    EXPECT_LE(*assigned_ip, conf.getAddrRange()->ip_addr_end);
}

TEST(NaiveIPAllocator, ExhaustIPPool)
{
    CTestLogger logger{0xFFFF};
    RamDatabase db{logger};
    DefaultConf conf;
    CTestTime time{0};

    NaiveIPAllocator ip_allocator{
        conf,
        logger,
        db,
        time
    };

    std::uint32_t ip_pool_size = conf.getAddrRange()->ip_addr_end - conf.getAddrRange()->ip_addr_start;
    std::vector<std::uint32_t> assigned_ips_list;
    assigned_ips_list.reserve(ip_pool_size);
    std::uint64_t mac;
    for (mac = 0; mac < ip_pool_size; ++mac)
    {
        std::optional<std::uint32_t> assigned_ip = ip_allocator.assign_free_ip(mac);
        EXPECT_TRUE(std::nullopt != assigned_ip);
        EXPECT_GE(*assigned_ip, conf.getAddrRange()->ip_addr_start);
        EXPECT_LE(*assigned_ip, conf.getAddrRange()->ip_addr_end);
        EXPECT_TRUE(assigned_ips_list.end() == std::find(assigned_ips_list.begin(), assigned_ips_list.end(), *assigned_ip));
        assigned_ips_list.push_back(*assigned_ip);
    }


    std::optional<std::uint32_t> assigned_ip = ip_allocator.assign_free_ip(mac);
    EXPECT_TRUE(std::nullopt == assigned_ip);
}

TEST(NaiveIPAllocator, AssignAlreadyAssignedIP)
{
    CTestLogger logger{0xFFFF};
    RamDatabase db{logger};
    DefaultConf conf;
    CTestTime time{0};

    NaiveIPAllocator ip_allocator{
        conf,
        logger,
        db,
        time
    };

    std::uint32_t ip_pool_size = conf.getAddrRange()->ip_addr_end - conf.getAddrRange()->ip_addr_start;
    std::vector<std::uint32_t> assigned_ips_list;
    assigned_ips_list.reserve(ip_pool_size);
    std::uint64_t mac;
    for (mac = 0; mac < ip_pool_size; ++mac)
    {
        std::optional<std::uint32_t> assigned_ip = ip_allocator.assign_free_ip(mac);
        EXPECT_TRUE(std::nullopt != assigned_ip);
        EXPECT_GE(*assigned_ip, conf.getAddrRange()->ip_addr_start);
        EXPECT_LE(*assigned_ip, conf.getAddrRange()->ip_addr_end);
        EXPECT_TRUE(assigned_ips_list.end() == std::find(assigned_ips_list.begin(), assigned_ips_list.end(), *assigned_ip));
        assigned_ips_list.push_back(*assigned_ip);
    }


    for (mac = 0; mac < ip_pool_size; ++mac)
    {
        std::optional<std::uint32_t> assigned_ip = ip_allocator.assign_free_ip(mac);
        EXPECT_TRUE(std::nullopt != assigned_ip);
        EXPECT_EQ(*assigned_ip, assigned_ips_list[mac]);
    }
}

TEST(NaiveIPAllocator, ReleaseIp)
{
    CTestLogger logger{0xFFFF};
    RamDatabase db{logger};
    DefaultConf conf;
    CTestTime time{0};

    NaiveIPAllocator ip_allocator{
        conf,
        logger,
        db,
        time
    };

    std::uint32_t ip_pool_size = conf.getAddrRange()->ip_addr_end - conf.getAddrRange()->ip_addr_start;
    std::vector<std::uint32_t> assigned_ips_list;
    assigned_ips_list.reserve(ip_pool_size);
    std::uint64_t mac;
    for (mac = 0; mac < ip_pool_size; ++mac)
    {
        std::optional<std::uint32_t> assigned_ip = ip_allocator.assign_free_ip(mac);
        assigned_ips_list.push_back(*assigned_ip);
    }

    // release ip of a fist mac
    ip_allocator.release_ip(0);

    // try to allocate new IP - as only one is free, we know which should be allocated
    std::optional<std::uint32_t> assigned_ip = ip_allocator.assign_free_ip(mac+10);
    EXPECT_TRUE(std::nullopt != assigned_ip);
    EXPECT_EQ(*assigned_ip, assigned_ips_list[0]);

    // IP pool is again exhausted
    assigned_ip = ip_allocator.assign_free_ip(mac+10+10);
    EXPECT_TRUE(std::nullopt == assigned_ip);
}

TEST(NaiveIPAllocator, ReleaseIpOfUnknownMac)
{
    CTestLogger logger{0xFFFF};
    RamDatabase db{logger};
    DefaultConf conf;
    CTestTime time{0};

    NaiveIPAllocator ip_allocator{
        conf,
        logger,
        db,
        time
    };

    std::uint64_t mac;
    for (mac = 0; mac < 10; ++mac)
    {
        std::optional<std::uint32_t> assigned_ip = ip_allocator.assign_free_ip(mac);
    }

    // release ip of a fist mac
    ip_allocator.release_ip(mac + 10);
}

TEST(NaiveIPAllocator, GarbageCollector)
{
    CTestLogger logger{0xFFFF};
    RamDatabase db{logger};
    DefaultConf conf;
    CTestTime time{0};

    NaiveIPAllocator ip_allocator{
        conf,
        logger,
        db,
        time
    };

    std::uint64_t mac;

    time.set_time(10);
    for (mac = 0; mac < 10; ++mac)
    {
        std::optional<std::uint32_t> assigned_ip = ip_allocator.assign_free_ip(mac);
        EXPECT_TRUE(std::nullopt != assigned_ip);
    }

    time.set_time(10 + (conf.getTimeouts()->lease_timeout / 2));
    for (mac = 10; mac < 20; ++mac)
    {
        std::optional<std::uint32_t> assigned_ip = ip_allocator.assign_free_ip(mac);
        EXPECT_TRUE(std::nullopt != assigned_ip);
    }

    time.set_time(10 + (conf.getTimeouts()->lease_timeout / 2) + 10);
    ip_allocator.garbage_collector();
    for (mac = 0; mac < 20; ++mac)
    {
        std::optional<struct client_model> client = db.get_client(mac);
        EXPECT_TRUE(std::nullopt != client);
    }

    time.set_time(10 + conf.getTimeouts()->lease_timeout + 10);
    ip_allocator.garbage_collector();
    for (mac = 0; mac < 10; ++mac)
    {
        std::optional<struct client_model> client = db.get_client(mac);
        EXPECT_TRUE(std::nullopt == client);
    }
    for (mac = 10; mac < 20; ++mac)
    {
        std::optional<struct client_model> client = db.get_client(mac);
        EXPECT_TRUE(std::nullopt != client);
    }
}



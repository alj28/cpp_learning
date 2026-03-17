#include <gtest/gtest.h>


#include "database_ram.hpp"
#include "ctest_logger.hpp"

const struct client_model test_client_1 = {
        .mac = 0x0102030405060708,
        .assigned_ip = 0x12345678,
        .lease_timeout = 0,
};

const struct client_model test_client_2 = {
        .mac = 0x090A0B0C0D0E0F10,
        .assigned_ip = 0x9ABCDEF0,
        .lease_timeout = 0,
};

TEST(RAMDatabase, AddClient) {
    CTestLogger logger{0xFFFF};
    RamDatabase db{logger};
    
    db.update_client(test_client_1);
    std::optional<struct client_model> test_client_1_readout_by_mac = db.get_client(test_client_1.mac);
    std::optional<struct client_model> test_client_1_readout_by_ip = db.get_client_by_ip(test_client_1.assigned_ip);
    EXPECT_TRUE(std::nullopt != test_client_1_readout_by_mac);
    EXPECT_TRUE(std::nullopt != test_client_1_readout_by_ip);
    EXPECT_TRUE(test_client_1 == test_client_1_readout_by_mac);

    std::optional<struct client_model> test_no_existing_client_readout_by_mac = db.get_client(test_client_2.mac);
    std::optional<struct client_model> test_no_existing_client_readout_by_ip = db.get_client_by_ip(test_client_2.assigned_ip);
    EXPECT_TRUE(std::nullopt == test_no_existing_client_readout_by_mac);
    EXPECT_TRUE(std::nullopt == test_no_existing_client_readout_by_ip);


    db.update_client(test_client_2);
    std::optional<struct client_model> test_client_2_readout_by_mac = db.get_client(test_client_2.mac);
    std::optional<struct client_model> test_client_2_readout_by_ip = db.get_client_by_ip(test_client_2.assigned_ip);
    EXPECT_TRUE(std::nullopt != test_client_2_readout_by_mac);
    EXPECT_TRUE(std::nullopt != test_client_2_readout_by_ip);

    struct client_model test_client_2_modified = test_client_2;
    test_client_2_modified.assigned_ip++;
    db.update_client(test_client_2_modified);
    std::optional<struct client_model> test_client_2_modified_readout_by_mac = db.get_client(test_client_2_modified.mac);
    std::optional<struct client_model> test_client_2_modified_readout_by_ip = db.get_client_by_ip(test_client_2_modified.assigned_ip);
    EXPECT_TRUE(std::nullopt != test_client_2_modified_readout_by_mac);
    EXPECT_TRUE(std::nullopt != test_client_2_modified_readout_by_ip);
}

TEST(RAMDatabase, RemoveClient) {
    CTestLogger logger{0xFFFF};
    RamDatabase db{logger};

    db.remove_client_by_ip(test_client_1.assigned_ip);
    db.remove_client_by_ip(test_client_1.mac);
    EXPECT_TRUE(std::nullopt == db.get_client_by_ip(test_client_1.assigned_ip));

    db.update_client(test_client_1);
    EXPECT_TRUE(std::nullopt != db.get_client_by_ip(test_client_1.assigned_ip));
    db.update_client(test_client_2);
    EXPECT_TRUE(std::nullopt != db.get_client_by_ip(test_client_2.assigned_ip));

    db.remove_client_by_ip(test_client_1.assigned_ip);
    db.remove_client_by_mac(test_client_2.mac);
    EXPECT_TRUE(std::nullopt == db.get_client_by_ip(test_client_1.assigned_ip));
    EXPECT_TRUE(std::nullopt == db.get_client_by_ip(test_client_2.assigned_ip));

};


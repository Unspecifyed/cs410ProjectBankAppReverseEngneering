#include <gtest/gtest.h>
#include "../bank.h"
#include "../client.h"

// Sample test for Bank class
TEST(BankTest, AddClient) {
    Bank bank;
    bank.AddClient("user1", "password123", 100, 50);
    // You would add more assertions depending on your Bank class implementation
    // For example:
    EXPECT_TRUE(bank.CheckUserPermissionAccess());  // Assuming this tests the access
}

// Sample test for Client class
TEST(ClientTest, DepositMoney) {
    Client client("user1", "passwordHash", 100, 50);
    bool success = client.deposit(50, 25);
    EXPECT_TRUE(success);
    EXPECT_EQ(client.getDollars(), 150);
    EXPECT_EQ(client.getCents(), 75);
}

// More tests would go here...

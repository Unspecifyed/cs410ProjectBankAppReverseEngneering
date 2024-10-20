#include <gtest/gtest.h>
#include "../bank.h"
#include "../client.h"
#include <fstream>

// Test fixture for Bank-related tests
class BankTest : public ::testing::Test {
protected:
    ClientMap clients;

    // Helper function to initialize some test clients
    void SetUp() override {
        addClient(clients, "testUser1", "password1", 100, 50);
        addClient(clients, "testUser2", "password2", 200, 75);
    }
};

// Test adding a client
TEST_F(BankTest, AddClient) {
    addClient(clients, "newUser", "newPassword", 150, 25);
    ASSERT_EQ(clients.size(), 3);
    ASSERT_EQ(clients["newUser"].checkingDollars, 150);
    ASSERT_EQ(clients["newUser"].checkingCents, 25);
}

// Test saving clients to JSON
TEST_F(BankTest, SaveClientsToJson) {
    saveClientsToJson(clients);
    std::ifstream inFile("clients.json");
    ASSERT_TRUE(inFile.is_open());
}

// Test loading clients from JSON
TEST_F(BankTest, LoadClientsFromJson) {
    saveClientsToJson(clients);
    ClientMap loadedClients;
    loadClientsFromJson(loadedClients);
    ASSERT_EQ(loadedClients.size(), clients.size());
    ASSERT_EQ(loadedClients["testUser1"].checkingDollars, clients["testUser1"].checkingDollars);
    ASSERT_EQ(loadedClients["testUser1"].checkingCents, clients["testUser1"].checkingCents);
}

// Test depositing into a client's account
TEST(ClientTest, Deposit) {
    Client client = {"testUser", "hashedPassword", 100, 50};
    bool success = deposit(client, 50, 25);
    ASSERT_TRUE(success);
    ASSERT_EQ(client.checkingDollars, 150);
    ASSERT_EQ(client.checkingCents, 75);
}

// Test withdrawing from a client's account
TEST(ClientTest, Withdraw) {
    Client client = {"testUser", "hashedPassword", 100, 50};
    bool success = withdraw(client, 50, 25);
    ASSERT_TRUE(success);
    ASSERT_EQ(client.checkingDollars, 50);
    ASSERT_EQ(client.checkingCents, 25);
}

// Test insufficient funds for withdrawal
TEST(ClientTest, WithdrawInsufficientFunds) {
    Client client = {"testUser", "hashedPassword", 50, 25};
    bool success = withdraw(client, 100, 0);  // Trying to withdraw more than available
    ASSERT_FALSE(success);
}

// Main function to run all tests
int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

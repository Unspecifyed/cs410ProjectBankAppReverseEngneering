
#ifndef CLIENT_H
#define CLIENT_H

#include <string>
#include <cstdint>

struct Client {
    std::string username;
    std::string passwordHash;
    unsigned int checkingDollars;
    uint8_t checkingCents;
};

bool deposit(Client& client, unsigned int dollars, uint8_t cents);
bool withdraw(Client& client, unsigned int dollars, uint8_t cents);
bool canDeposit(const Client& client, unsigned int dollars, uint8_t cents);
bool canWithdraw(const Client& client, unsigned int dollars, uint8_t cents);

#endif  // CLIENT_H
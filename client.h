#ifndef CLIENT_H
#define CLIENT_H

#include <string>
#include <cstdint>  // For uint8_t

class Client {
public:
    Client(const std::string& username, const std::string& passwordHash, unsigned int dollars, uint8_t cents);

    std::string getUsername() const;
    std::string getPasswordHash() const;
    unsigned int getDollars() const;
    uint8_t getCents() const;
    bool deposit(unsigned int dollars, uint8_t cents);
    bool withdraw(unsigned int dollars, uint8_t cents);

private:
    std::string username;
    std::string passwordHash;
    unsigned int checkingDollars;
    uint8_t checkingCents;

    bool canDeposit(unsigned int dollars, uint8_t cents) const;
    bool canWithdraw(unsigned int dollars, uint8_t cents) const;
};

#endif  // CLIENT_H

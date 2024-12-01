
#ifndef CLIENT_H
#define CLIENT_H

#include <string>
#include <cstdint>
#include <iostream>

class Client {
public:
    Client(const std::string &username, const std::string &passwordHash, unsigned int dollars, uint8_t cents);

    // Getters and setters
    const std::string &getUsername() const;
    const std::string &getPasswordHash() const;
    unsigned int getCheckingDollars() const;
    uint8_t getCheckingCents() const;

    void setOverdraftLimit(int limit);  // New
    int getOverdraftLimit() const;     // New

    void applyInterest(double rate);  // New

    // Operations
    bool deposit(unsigned int dollars, uint8_t cents);
    bool withdraw(unsigned int dollars, uint8_t cents);

private:
    std::string username;
    std::string passwordHash;
    unsigned int checkingDollars;
    uint8_t checkingCents;
    int overdraftLimit;  // New: Overdraft protection

    // Helper functions
    bool validateAmount(unsigned int dollars, uint8_t cents) const;
    bool hasSufficientFunds(unsigned int dollars, uint8_t cents) const;
};

#endif  // CLIENT_H

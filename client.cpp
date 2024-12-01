
#include "client.h"
#include <stdexcept>

// Constructor
Client::Client(const std::string &username, const std::string &passwordHash, unsigned int dollars, uint8_t cents)
    : username(username), passwordHash(passwordHash), checkingDollars(dollars), checkingCents(cents), overdraftLimit(0) {}

// Getters and setters
const std::string &Client::getUsername() const {
    return username;
}

const std::string &Client::getPasswordHash() const {
    return passwordHash;
}

unsigned int Client::getCheckingDollars() const {
    return checkingDollars;
}

uint8_t Client::getCheckingCents() const {
    return checkingCents;
}

void Client::setOverdraftLimit(int limit) {
    overdraftLimit = limit;
}

int Client::getOverdraftLimit() const {
    return overdraftLimit;
}

void Client::applyInterest(double rate) {
    if (rate < 0) {
        throw std::invalid_argument("Interest rate cannot be negative.");
    }

    unsigned int totalCents = checkingDollars * 100 + checkingCents;
    totalCents = static_cast<unsigned int>(totalCents * (1 + rate));

    checkingDollars = totalCents / 100;
    checkingCents = totalCents % 100;
}

// Helper functions
bool Client::validateAmount(unsigned int dollars, uint8_t cents) const {
    if (dollars == 0 && cents == 0) {
        std::cerr << "[ERROR] Amount cannot be zero." << std::endl;
        return false;
    }
    return true;
}

bool Client::hasSufficientFunds(unsigned int dollars, uint8_t cents) const {
    int availableFunds = static_cast<int>(checkingDollars) * 100 + checkingCents;
    int requestedAmount = static_cast<int>(dollars) * 100 + cents;

    return availableFunds + overdraftLimit * 100 >= requestedAmount;
}

// Operations
bool Client::deposit(unsigned int dollars, uint8_t cents) {
    if (!validateAmount(dollars, cents)) {
        return false;
    }

    unsigned int totalCents = checkingDollars * 100 + checkingCents + dollars * 100 + cents;

    checkingDollars = totalCents / 100;
    checkingCents = totalCents % 100;

    return true;
}

bool Client::withdraw(unsigned int dollars, uint8_t cents) {
    if (!validateAmount(dollars, cents)) {
        return false;
    }

    if (!hasSufficientFunds(dollars, cents)) {
        std::cerr << "[ERROR] Insufficient funds with overdraft protection." << std::endl;
        return false;
    }

    int totalCents = checkingDollars * 100 + checkingCents - dollars * 100 - cents;

    if (totalCents < 0) {
        checkingDollars = 0;
        checkingCents = static_cast<uint8_t>(-totalCents);
    } else {
        checkingDollars = totalCents / 100;
        checkingCents = totalCents % 100;
    }

    return true;
}

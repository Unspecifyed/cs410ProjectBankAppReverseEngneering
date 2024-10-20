#include "client.h"
#include <iostream>
#include <limits>

Client::Client(const std::string& username, const std::string& passwordHash, unsigned int dollars, uint8_t cents)
    : username(username), passwordHash(passwordHash), checkingDollars(dollars), checkingCents(cents) {}

std::string Client::getUsername() const {
    return username;
}

std::string Client::getPasswordHash() const {
    return passwordHash;
}

unsigned int Client::getDollars() const {
    return checkingDollars;
}

uint8_t Client::getCents() const {
    return checkingCents;
}

bool Client::canDeposit(unsigned int dollars, uint8_t cents) const {
    if (checkingDollars > std::numeric_limits<unsigned int>::max() - dollars) {
        std::cout << "Deposit would cause an overflow. Please try a smaller amount." << std::endl;
        return false;
    }

    unsigned int totalCents = checkingCents + cents;
    if (totalCents >= 100 && checkingDollars == std::numeric_limits<unsigned int>::max()) {
        std::cout << "Deposit would cause an overflow. Please try a smaller amount." << std::endl;
        return false;
    }

    return true;
}

bool Client::canWithdraw(unsigned int dollars, uint8_t cents) const {
    if (checkingDollars < dollars || (checkingDollars == dollars && checkingCents < cents)) {
        std::cout << "Insufficient funds for withdrawal." << std::endl;
        return false;
    }

    return true;
}

bool Client::deposit(unsigned int dollars, uint8_t cents) {
    if (!canDeposit(dollars, cents)) {
        return false;
    }

    checkingDollars += dollars;
    checkingCents += cents;

    if (checkingCents >= 100) {
        checkingDollars += checkingCents / 100;
        checkingCents = checkingCents % 100;
    }

    return true;
}

bool Client::withdraw(unsigned int dollars, uint8_t cents) {
    if (!canWithdraw(dollars, cents)) {
        return false;
    }

    checkingDollars -= dollars;

    if (checkingCents < cents) {
        checkingDollars -= 1;
        checkingCents = 100 + checkingCents - cents;
    } else {
        checkingCents -= cents;
    }

    return true;
}

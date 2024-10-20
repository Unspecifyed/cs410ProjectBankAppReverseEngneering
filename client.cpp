#include "client.h"
#include <iostream>
#include <limits>

bool canDeposit(const Client& client, unsigned int dollars, uint8_t cents) {
    // First, check if adding cents causes an overflow
    uint8_t newCents = client.checkingCents + cents;
    unsigned int carryOverDollars = 0;

    // If the cents are 100 or more, we need to carry over to dollars
    if (newCents >= 100) {
        carryOverDollars = newCents / 100;  // Determine how many dollars to carry over
        newCents = newCents % 100;  // Remaining cents after carry-over
    }

    // Check for dollar overflow when adding both the dollars and the carry-over
    if (client.checkingDollars > std::numeric_limits<unsigned int>::max() - dollars - carryOverDollars) {
        std::cout << "Overflow detected in deposit." << std::endl;
        return false;
    }

    // If no overflow detected, return true
    return true;
}

bool canWithdraw(const Client& client, unsigned int dollars, uint8_t cents) {
    if (client.checkingDollars < dollars || 
        (client.checkingDollars == dollars && client.checkingCents < cents)) {
        std::cout << "Insufficient funds." << std::endl;
        return false;
    }
    return true;
}

bool deposit(Client& client, unsigned int dollars, uint8_t cents) {
    if (!canDeposit(client, dollars, cents)) {
        return false;
    }
    client.checkingDollars += dollars;
    client.checkingCents += cents;
    if (client.checkingCents >= 100) {
        client.checkingDollars += client.checkingCents / 100;
        client.checkingCents = client.checkingCents % 100;
    }
    return true;
}

bool withdraw(Client& client, unsigned int dollars, uint8_t cents) {
    if (!canWithdraw(client, dollars, cents)) {
        return false;
    }
    client.checkingDollars -= dollars;
    if (client.checkingCents < cents) {
        client.checkingDollars -= 1;
        client.checkingCents = 100 + client.checkingCents - cents;
    } else {
        client.checkingCents -= cents;
    }
    return true;
}

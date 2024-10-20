#include "client.h"
#include <iostream>

bool canDeposit(const Client& client, unsigned int dollars, uint8_t cents) {
    (void)cents;  // Mark 'cents' as intentionally unused
    if (client.checkingDollars + dollars < client.checkingDollars) {
        std::cout << "Overflow detected in deposit." << std::endl;
        return false;
    }
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

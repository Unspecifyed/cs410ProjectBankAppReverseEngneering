#include "bank.h"
#include <iostream>

int main() {
    ClientMap clients;
    loadClientsFromJson(clients);

    std::string username, password;
    std::cout << "Enter username: ";
    std::cin >> username;
    std::cout << "Enter password: ";
    std::cin >> password;

    addClient(clients, username, password, 100, 50);

    saveClientsToJson(clients);
    return 0;
}

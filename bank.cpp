#include "bank.h"
#include <iostream>
#include <stdexcept>

Bank::Bank() {
    try {
        loadClients();
    } catch (const std::exception &e) {
        std::cerr << "[ERROR] Failed to initialize bank: " << e.what() << std::endl;
    }
}

void Bank::addClient(const std::string &username, const std::string &password, unsigned int dollars, uint8_t cents) {
    if (username.empty() || password.empty()) {
        std::cerr << "[ERROR] Username or password cannot be empty." << std::endl;
        return;
    }
    if (clients.find(username) != clients.end()) {
        std::cerr << "[ERROR] Client already exists: " << username << std::endl;
        return;
    }

    try {
        clients[username] = Client(username, authenticator.hashPassword(password), dollars, cents);
        std::cout << "[INFO] Client added successfully: " << username << std::endl;
    } catch (const std::exception &e) {
        std::cerr << "[ERROR] Failed to add client: " << e.what() << std::endl;
    }
}

void Bank::loadClients() {
    try {
        clients = persistenceManager.loadClientsFromDatabase();
        std::cout << "[INFO] Clients loaded successfully." << std::endl;
    } catch (const std::exception &e) {
        std::cerr << "[ERROR] Error loading clients: " << e.what() << std::endl;
        // Handle fallback, e.g., load defaults or start with empty clients map
        clients.clear();
    }
}

void Bank::saveClients() {
    try {
        persistenceManager.saveClientsToDatabase(clients);
        std::cout << "[INFO] Clients saved successfully." << std::endl;
    } catch (const std::exception &e) {
        std::cerr << "[ERROR] Error saving clients: " << e.what() << std::endl;
    }
}

bool Bank::authenticateClient(const std::string &username, const std::string &password) {
    if (clients.find(username) == clients.end()) {
        std::cerr << "[WARN] Authentication failed: Client does not exist: " << username << std::endl;
        return false;
    }

    try {
        bool isAuthenticated = authenticator.verifyPassword(password, clients[username].getPasswordHash());
        if (isAuthenticated) {
            std::cout << "[INFO] Authentication successful for client: " << username << std::endl;
        } else {
            std::cerr << "[WARN] Authentication failed for client: " << username << std::endl;
        }
        return isAuthenticated;
    } catch (const std::exception &e) {
        std::cerr << "[ERROR] Error during authentication: " << e.what() << std::endl;
        return false;
    }
}

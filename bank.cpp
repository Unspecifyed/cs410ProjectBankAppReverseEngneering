#include "bank.h"
#include <iostream>

Bank::Bank() { loadClients(); }

void Bank::addClient(const std::string &username, const std::string &password,
                     unsigned int dollars, uint8_t cents) {
  if (clients.find(username) != clients.end()) {
    std::cerr << "Client already exists." << std::endl;
    return;
  }
  clients[username] =
      Client(username, authenticator.hashPassword(password), dollars, cents);
}

void Bank::loadClients() {
  try {
    clients = persistenceManager.loadClientsFromDatabase();
  } catch (const std::exception &e) {
    std::cerr << "Error loading clients: " << e.what() << std::endl;
  }
}

void Bank::saveClients() {
  try {
    persistenceManager.saveClientsToDatabase(clients);
  } catch (const std::exception &e) {
    std::cerr << "Error saving clients: " << e.what() << std::endl;
  }
}

bool Bank::authenticateClient(const std::string &username,
                              const std::string &password) {
  if (clients.find(username) == clients.end()) {
    return false;
  }
  return authenticator.verifyPassword(password,
                                      clients[username].getPasswordHash());
}
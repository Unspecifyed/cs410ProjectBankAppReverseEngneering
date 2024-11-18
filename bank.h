#ifndef BANK_H
#define BANK_H

#include "authenticator.h"
#include "client.h"
#include "persistence_manager.h"
#include <string>
#include <unordered_map>

class Bank {
private:
  std::unordered_map<std::string, Client> clients;
  PersistenceManager persistenceManager;
  Authenticator authenticator;

public:
  Bank();
  void addClient(const std::string &username, const std::string &password,
                 unsigned int dollars, uint8_t cents);
  void loadClients();
  void saveClients();
  bool authenticateClient(const std::string &username,
                          const std::string &password);
};

#endif // BANK_H
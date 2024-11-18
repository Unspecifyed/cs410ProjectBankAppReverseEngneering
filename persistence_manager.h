#ifndef PERSISTENCE_MANAGER_H
#define PERSISTENCE_MANAGER_H

#include "client.h"
#include <string>
#include <unordered_map>

class PersistenceManager {
public:
  std::unordered_map<std::string, Client> loadClientsFromDatabase();
  void
  saveClientsToDatabase(const std::unordered_map<std::string, Client> &clients);
};

#endif // PERSISTENCE_MANAGER_H
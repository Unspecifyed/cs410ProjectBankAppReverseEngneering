#include "persistence_manager.h"
#include "serializer.h"
#include <fstream>
#include <iostream>
#include <stdexcept>

void PersistenceManager::saveClientsToDatabase(const std::unordered_map<std::string, Client> &clients) {
    std::ofstream ofs("clients.dat", std::ios::binary);
    if (!ofs) {
        throw std::runtime_error("Failed to open file for writing.");
    }

    Serializer::serializeMap(ofs, clients);
    ofs.close();
    std::cout << "Clients saved to database.\n";
}

std::unordered_map<std::string, Client> PersistenceManager::loadClientsFromDatabase() {
    std::ifstream ifs("clients.dat", std::ios::binary);
    if (!ifs) {
        std::cout << "No database file found, returning empty map.\n";
        return {};
    }

    auto clients = Serializer::deserializeMap(ifs);
    ifs.close();
    std::cout << "Clients loaded from database.\n";
    return clients;
}

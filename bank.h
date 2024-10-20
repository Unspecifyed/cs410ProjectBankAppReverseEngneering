#ifndef BANK_H
#define BANK_H

#include "client.h"
#include <string>
#include <unordered_map>

using ClientMap = std::unordered_map<std::string, Client>;

void addClient(ClientMap& clients, const std::string& username, const std::string& password, unsigned int dollars, uint8_t cents);
void loadClientsFromJson(ClientMap& clients);
void saveClientsToJson(const ClientMap& clients);
std::string hashPassword(const std::string& password);

#endif  // BANK_H

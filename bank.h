#ifndef BANK_H
#define BANK_H

#include "client.h"
#include <string>
#include <unordered_map>

class Bank {
public:
    Bank();
    ~Bank();

    void RunProgram();
    void AddClient(const std::string& username, const std::string& password, unsigned int dollars, uint8_t cents);
    bool CheckUserPermissionAccess();
    void DisplayInfo();
    
private:
    std::unordered_map<std::string, Client> clients;

    void LoadClientsFromJson();
    void SaveClientsToJson() const;
    std::string HashPassword(const std::string& password) const;
};

#endif  // BANK_H

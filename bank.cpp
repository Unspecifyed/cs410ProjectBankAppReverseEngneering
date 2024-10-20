#include "bank.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <jsoncpp/json/json.h>
#include <openssl/sha.h>

Bank::Bank() {
    LoadClientsFromJson();
}

Bank::~Bank() {
    SaveClientsToJson();
}

void Bank::LoadClientsFromJson() {
    std::ifstream inFile("clients.json");
    if (!inFile.is_open()) {
        std::cerr << "No client data found, starting fresh." << std::endl;
        return;
    }

    Json::Value root;
    inFile >> root;

    for (const auto& clientJson : root["clients"]) {
        std::string username = clientJson["username"].asString();
        std::string passwordHash = clientJson["passwordHash"].asString();
        unsigned int dollars = clientJson["dollars"].asUInt();
        uint8_t cents = static_cast<uint8_t>(clientJson["cents"].asUInt());

        clients.emplace(username, Client(username, passwordHash, dollars, cents));
    }

    inFile.close();
}

void Bank::SaveClientsToJson() const {
    Json::Value root;
    Json::Value clientList(Json::arrayValue);

    for (const auto& [username, client] : clients) {
        Json::Value clientJson;
        clientJson["username"] = client.getUsername();
        clientJson["passwordHash"] = client.getPasswordHash();
        clientJson["dollars"] = client.getDollars();
        clientJson["cents"] = client.getCents();
        clientList.append(clientJson);
    }

    root["clients"] = clientList;

    std::ofstream outFile("clients.json");
    outFile << root;
    outFile.close();
}

void Bank::RunProgram() {
    int userChoice = 0;
    do {
        std::cout << "1. DISPLAY the client list\n";
        std::cout << "2. Exit the program\n";
        std::cin >> userChoice;

        if (userChoice == 1) {
            DisplayInfo();
        } else if (userChoice != 2) {
            std::cout << "Invalid option, please try again." << std::endl;
        }
    } while (userChoice != 2);
}

void Bank::AddClient(const std::string& username, const std::string& password, unsigned int dollars, uint8_t cents) {
    std::string passwordHash = HashPassword(password);
    clients.emplace(username, Client(username, passwordHash, dollars, cents));
}

bool Bank::CheckUserPermissionAccess() {
    std::string username, password;
    std::cout << "Enter your username: ";
    std::cin >> username;
    std::cout << "Enter your password: ";
    std::cin >> password;

    auto it = clients.find(username);
    if (it != clients.end() && it->second.getPasswordHash() == HashPassword(password)) {
        std::cout << "Access granted." << std::endl;
        return true;
    } else {
        std::cout << "Invalid username or password." << std::endl;
        return false;
    }
}

void Bank::DisplayInfo() {
    std::cout << "Client's Name    Balance (Dollars.Cents)\n";
    std::cout << "----------------------------------------\n";
    for (const auto& [username, client] : clients) {
        std::cout << username << "    " << client.getDollars() << "." << (int)client.getCents() << std::endl;
    }
}

std::string Bank::HashPassword(const std::string& password) const {
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256((unsigned char*)password.c_str(), password.size(), hash);
    std::stringstream ss;
    for (int i = 0; i < SHA256_DIGEST_LENGTH; ++i) {
        ss << std::hex << (int)hash[i];
    }
    return ss.str();
}

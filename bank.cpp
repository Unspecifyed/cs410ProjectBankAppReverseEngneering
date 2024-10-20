#include "bank.h"
#include <iostream>
#include <fstream>
#include <jsoncpp/json/json.h>
#include <openssl/sha.h>
#include <iomanip>
#include <vector>

void addClient(ClientMap& clients, const std::string& username, const std::string& password, unsigned int dollars, uint8_t cents) {
    clients[username] = Client{username, hashPassword(password), dollars, cents};
}

void loadClientsFromJson(ClientMap& clients) {
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

        clients[username] = Client{username, passwordHash, dollars, cents};
    }
}

void saveClientsToJson(const ClientMap& clients) {
    Json::Value root;
    Json::Value clientList(Json::arrayValue);

    for (const auto& [username, client] : clients) {
        Json::Value clientJson;
        clientJson["username"] = client.username;
        clientJson["passwordHash"] = client.passwordHash;
        clientJson["dollars"] = client.checkingDollars;
        clientJson["cents"] = client.checkingCents;

        clientList.append(clientJson);
    }

    root["clients"] = clientList;

    std::ofstream outFile("clients.json");
    outFile << root;
}

std::string hashPassword(const std::string& password) {
    // Declare a vector to hold the hash result
    std::vector<unsigned char> hash(SHA256_DIGEST_LENGTH);  // SHA256_DIGEST_LENGTH is a constant size

    // Generate the SHA256 hash and store it in the vector
    SHA256(reinterpret_cast<const unsigned char*>(password.c_str()), password.length(), hash.data());

    // Convert the vector of bytes to a string (hexadecimal)
    std::stringstream ss;
    for (unsigned char byte : hash) {
        ss << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(byte);
    }

    return ss.str();  // Return the hash as a hex string
}

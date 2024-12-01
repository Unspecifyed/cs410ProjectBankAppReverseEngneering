#include "serializer.h"

void Serializer::serializeClient(std::ofstream &ofs, const Client &client) {
    size_t usernameLength = client.username.size();
    ofs.write(reinterpret_cast<const char*>(&usernameLength), sizeof(usernameLength));
    ofs.write(client.username.data(), usernameLength);

    size_t passwordLength = client.passwordHash.size();
    ofs.write(reinterpret_cast<const char*>(&passwordLength), sizeof(passwordLength));
    ofs.write(client.passwordHash.data(), passwordLength);

    ofs.write(reinterpret_cast<const char*>(&client.checkingDollars), sizeof(client.checkingDollars));
    ofs.write(reinterpret_cast<const char*>(&client.checkingCents), sizeof(client.checkingCents));
}

Client Serializer::deserializeClient(std::ifstream &ifs) {
    Client client;

    size_t usernameLength;
    ifs.read(reinterpret_cast<char*>(&usernameLength), sizeof(usernameLength));
    client.username.resize(usernameLength);
    ifs.read(&client.username[0], usernameLength);

    size_t passwordLength;
    ifs.read(reinterpret_cast<char*>(&passwordLength), sizeof(passwordLength));
    client.passwordHash.resize(passwordLength);
    ifs.read(&client.passwordHash[0], passwordLength);

    ifs.read(reinterpret_cast<char*>(&client.checkingDollars), sizeof(client.checkingDollars));
    ifs.read(reinterpret_cast<char*>(&client.checkingCents), sizeof(client.checkingCents));

    return client;
}

void Serializer::serializeMap(std::ofstream &ofs, const std::unordered_map<std::string, Client> &clients) {
    size_t mapSize = clients.size();
    ofs.write(reinterpret_cast<const char*>(&mapSize), sizeof(mapSize));

    for (const auto &[key, client] : clients) {
        size_t keyLength = key.size();
        ofs.write(reinterpret_cast<const char*>(&keyLength), sizeof(keyLength));
        ofs.write(key.data(), keyLength);

        serializeClient(ofs, client);
    }
}

std::unordered_map<std::string, Client> Serializer::deserializeMap(std::ifstream &ifs) {
    std::unordered_map<std::string, Client> clients;

    size_t mapSize;
    ifs.read(reinterpret_cast<char*>(&mapSize), sizeof(mapSize));

    for (size_t i = 0; i < mapSize; ++i) {
        size_t keyLength;
        ifs.read(reinterpret_cast<char*>(&keyLength), sizeof(keyLength));
        std::string key(keyLength, '\0');
        ifs.read(&key[0], keyLength);

        Client client = deserializeClient(ifs);
        clients[key] = client;
    }

    return clients;
}

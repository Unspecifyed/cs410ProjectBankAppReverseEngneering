#ifndef SERIALIZER_H
#define SERIALIZER_H

#include "client.h"
#include <unordered_map>
#include <string>
#include <fstream>

class Serializer {
public:
    static void serializeClient(std::ofstream &ofs, const Client &client);
    static Client deserializeClient(std::ifstream &ifs);

    static void serializeMap(std::ofstream &ofs, const std::unordered_map<std::string, Client> &clients);
    static std::unordered_map<std::string, Client> deserializeMap(std::ifstream &ifs);
};

#endif  // SERIALIZER_H

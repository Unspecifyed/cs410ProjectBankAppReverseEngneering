
#include "authenticator.h"
#include <iomanip>
#include <openssl/sha.h>
#include <sstream>
#include <stdexcept>
#include <random>

std::string generateSalt(size_t length = 16) {
    static const char charset[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    static std::random_device rd;
    static std::mt19937 generator(rd());
    static std::uniform_int_distribution<size_t> dist(0, sizeof(charset) - 2);

    std::string salt;
    for (size_t i = 0; i < length; ++i) {
        salt += charset[dist(generator)];
    }
    return salt;
}

std::string Authenticator::hashPassword(const std::string &password, const std::string &salt) {
    // Create SHA256 hash of the password with salt
    std::string saltedPassword = salt + password;
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256((const unsigned char *)saltedPassword.c_str(), saltedPassword.size(), hash);

    // Convert hash to a hexadecimal string
    std::stringstream ss;
    for (int i = 0; i < SHA256_DIGEST_LENGTH; ++i) {
        ss << std::hex << std::setw(2) << std::setfill('0') << (int)hash[i];
    }

    return salt + ":" + ss.str(); // Combine salt and hash for storage
}

bool Authenticator::verifyPassword(const std::string &password, const std::string &storedHash) {
    // Split stored hash into salt and hash
    size_t delimiterPos = storedHash.find(':');
    if (delimiterPos == std::string::npos) {
        throw std::invalid_argument("Invalid stored hash format");
    }
    std::string salt = storedHash.substr(0, delimiterPos);
    std::string hash = storedHash.substr(delimiterPos + 1);

    // Hash the input password with the extracted salt and compare with the stored hash
    return hashPassword(password, salt) == storedHash;
}

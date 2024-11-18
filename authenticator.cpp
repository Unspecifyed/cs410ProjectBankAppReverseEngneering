#include "authenticator.h"
#include <iomanip>
#include <openssl/sha.h>
#include <sstream>
#include <stdexcept>

std::string Authenticator::hashPassword(const std::string &password) {
  // Create SHA256 hash of the password
  unsigned char hash[SHA256_DIGEST_LENGTH];
  SHA256((const unsigned char *)password.c_str(), password.size(), hash);

  // Convert hash to a hexadecimal string
  std::stringstream ss;
  for (int i = 0; i < SHA256_DIGEST_LENGTH; ++i) {
    ss << std::hex << std::setw(2) << std::setfill('0') << (int)hash[i];
  }

  return ss.str();
}

bool Authenticator::verifyPassword(const std::string &password,
                                   const std::string &hash) {
  // Hash the input password and compare with the given hash
  return hashPassword(password) == hash;
}

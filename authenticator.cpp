#include "authenticator.h"
#include <bcrypt/BCrypt.hpp>

std::string Authenticator::hashPassword(const std::string &password) {
  return BCrypt::generateHash(password);
}

bool Authenticator::verifyPassword(const std::string &password,
                                   const std::string &hash) {
  return BCrypt::validatePassword(password, hash);
}
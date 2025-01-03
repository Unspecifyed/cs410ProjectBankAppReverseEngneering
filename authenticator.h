#ifndef AUTHENTICATOR_H
#define AUTHENTICATOR_H

#include <crypt.h>
#include <string>

class Authenticator {
public:
  // Hashes the password using crypt_blowfish library
std::string Authenticator::hashPassword(const std::string &password, const std::string &salt) {

  // Verifies the password against the given hash
  bool verifyPassword(const std::string &password, const std::string &hash);
};

#endif // AUTHENTICATOR_H

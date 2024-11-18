#ifndef AUTHENTICATOR_H
#define AUTHENTICATOR_H

#include <string>

class Authenticator {
public:
  std::string hashPassword(const std::string &password);
  bool verifyPassword(const std::string &password, const std::string &hash);
};

#endif // AUTHENTICATOR_H
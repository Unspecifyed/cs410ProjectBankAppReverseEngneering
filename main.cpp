#include "bank.h"
#include <iostream>

int main() {
  Bank bank;

  std::string username, password;
  std::cout << "Enter username: ";
  std::cin >> username;
  std::cout << "Enter password: ";
  std::cin >> password;

  if (bank.authenticateClient(username, password)) {
    std::cout << "Authentication successful." << std::endl;
  } else {
    std::cerr << "Authentication failed." << std::endl;
  }

  bank.addClient("new_user", "new_password", 100, 50);
  bank.saveClients();

  return 0;
}
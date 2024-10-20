#include "bank.h"
#include <iostream>

void Bank::ChangeCustomerChoice() {
    int choice = 0;
    std::cout << "Enter the number of the client that you wish to change: ";
    std::cin >> choice;

    if (choice == 1) {
        std::cout << "Client 1 selected. New service: Brokerage." << std::endl;
    } else if (choice == 2) {
        std::cout << "Client 2 selected. New service: Retirement." << std::endl;
    } else if (choice == 3) {
        std::cout << "Client 3 selected. New service: Brokerage." << std::endl;
    } else if (choice == 4) {
        std::cout << "Client 4 selected. New service: Retirement." << std::endl;
    } else if (choice == 5) {
        std::cout << "Client 5 selected. New service: Brokerage." << std::endl;
    } else {
        std::cout << "Invalid client number." << std::endl;
    }
}

bool Bank::CheckUserPermissionAccess() {
    std::string username, password;
    std::cout << "Enter your username: ";
    std::cin >> username;
    std::cout << "Enter your password: ";
    std::cin >> password;

    if (username == "admin" && password == "password") {
        std::cout << "Access granted." << std::endl;
        return true;
    } else {
        std::cout << "Invalid username or password." << std::endl;
        return false;
    }
}

void Bank::DisplayInfo() {
    std::cout << "Client's Name    Service Selected (1 = Brokerage, 2 = Retirement)" << std::endl;
    std::cout << "----------------------------------------" << std::endl;
    std::cout << "Bob Jones    1" << std::endl;
    std::cout << "Sarah Davis  2" << std::endl;
    std::cout << "Amy Friendly 1" << std::endl;
    std::cout << "Johnny Smith 2" << std::endl;
    std::cout << "Carol Spears 1" << std::endl;
}

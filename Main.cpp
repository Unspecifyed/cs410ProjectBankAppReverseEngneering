#include "bank.h"
#include <iostream>

int main() {
    int userChoice = 0;
    Bank bank;  // Create an instance of the Bank class

    do {
        std::cout << "What would you like to do?" << std::endl;
        std::cout << "1. DISPLAY the client list (enter 1)" << std::endl;
        std::cout << "2. CHANGE a client's choice (enter 2)" << std::endl;
        std::cout << "3. Exit the program (enter 3)" << std::endl;
        std::cin >> userChoice;

        if (userChoice == 1) {
            bank.DisplayInfo();
        } else if (userChoice == 2) {
            bank.ChangeCustomerChoice();
        } else if (userChoice != 3) {
            std::cout << "Invalid option, please try again." << std::endl;
        }
    } while (userChoice != 3);

    std::cout << "Exiting the program..." << std::endl;
    return 0;
}

#include <iostream>
#include <string>
#include <vector>
#include <memory> // For std::unique_ptr
#include <new>

// Simulated structure containing user information
struct UserProfile {
    std::string username;
    int age;
    std::string accessLevel;

    UserProfile(const std::string& username, int age, const std::string& accessLevel)
        : username(username), age(age), accessLevel(accessLevel) {
        std::cout << "UserProfile for " << username << " initialized." << std::endl;
    }

    ~UserProfile() {
        std::cout << "UserProfile for " << username << " destroyed." << std::endl;
    }
};

// Global vector of user profiles
std::vector<std::unique_ptr<UserProfile>> userProfiles;

// Pointer to the currently active user profile
std::unique_ptr<UserProfile> activeUserProfile = nullptr;

// This function simulates the initialization of a new user profile.
void initializeProfile(const std::string& username, int age, const std::string& accessLevel) {
    // Create a new user profile and add it to the vector
    auto newProfile = std::make_unique<UserProfile>(username, age, accessLevel);
    userProfiles.push_back(std::move(newProfile));

    // Set the newly created profile as the active one
    activeUserProfile = std::move(userProfiles.back());
    std::cout << "Profile for " << activeUserProfile->username << " is now active." << std::endl;
}

// Function to display information from the active user profile.
void DisplayInfo() {
    if (activeUserProfile) {
        std::cout << "Displaying active user profile information..." << std::endl;
        std::cout << "Username: " << activeUserProfile->username << std::endl;
        std::cout << "Age: " << activeUserProfile->age << std::endl;
        std::cout << "Access Level: " << activeUserProfile->accessLevel << std::endl;
        std::cout << "Information display completed." << std::endl;
    } else {
        std::cout << "No active user profile available to display." << std::endl;
    }
}

// Function to modify the active user profile data.
void ModifyProfile() {
    if (activeUserProfile) {
        std::string newUsername;
        int newAge;
        std::string newAccessLevel;

        std::cout << "Enter new username: ";
        std::cin >> newUsername;
        std::cout << "Enter new age: ";
        std::cin >> newAge;
        std::cout << "Enter new access level (e.g., Admin, User): ";
        std::cin >> newAccessLevel;

        activeUserProfile->username = newUsername;
        activeUserProfile->age = newAge;
        activeUserProfile->accessLevel = newAccessLevel;

        std::cout << "Profile updated successfully!" << std::endl;
    } else {
        std::cout << "No active user profile available to modify." << std::endl;
    }
}

// Function simulating user permission access check.
int CheckUserPermissionAccess() {
    std::cout << "Checking user permission..." << std::endl;

    if (activeUserProfile && activeUserProfile->accessLevel == "Admin") {
        std::cout << "Permission granted." << std::endl;
        return 1;  // Permission granted
    } else {
        std::cout << "Permission denied." << std::endl;
        return 2;  // Permission denied
    }
}

// Function to delete the active user profile.
void DeleteProfile() {
    if (!activeUserProfile) {
        std::cout << "No active user profile available to delete." << std::endl;
        return;
    }

    // Find the active profile in the vector and remove it
    for (auto it = userProfiles.begin(); it != userProfiles.end(); ++it) {
        if ((*it)->username == activeUserProfile->username) {
            userProfiles.erase(it);  // Remove the profile from the vector
            activeUserProfile.reset();  // Reset the unique_ptr, releasing memory
            std::cout << "Active profile deleted successfully." << std::endl;
            return;
        }
    }

    std::cout << "Profile not found in list." << std::endl;
}

// Function to switch active user profiles based on username.
void SwitchProfile() {
    if (userProfiles.empty()) {
        std::cout << "No user profiles available to switch to." << std::endl;
        return;
    }

    std::string usernameToSwitch;
    std::cout << "Enter the username of the profile you want to switch to: ";
    std::cin >> usernameToSwitch;

    // Search for the profile with the matching username
    for (size_t i = 0; i < userProfiles.size(); ++i) {
        if (userProfiles[i]->username == usernameToSwitch) {
            activeUserProfile = std::move(userProfiles[i]);
            std::cout << "Switched to profile: " << activeUserProfile->username << std::endl;
            return;
        }
    }

    // If no matching username is found
    std::cout << "Profile with username \"" << usernameToSwitch << "\" not found." << std::endl;
}

int main() {
    int customerChoice = 0;

    std::cout << "CS410 Project 1 Francis Cottrell-Eshaghi" << std::endl; 
    std::cout << "Reversed Engineering the functonality the user program and refactored to modern code." << std::endl; 
    std::cout << "Welcome to User Profile Management System!" << std::endl; 

    while (true) {
        // Display menu options
        std::cout << "\n--- User Profile Menu ---" << std::endl;
        std::cout << "1. View Active Profile" << std::endl;
        std::cout << "2. Modify Active Profile" << std::endl;
        std::cout << "3. Check Permission" << std::endl;
        std::cout << "4. Exit" << std::endl;
        std::cout << "5. Delete Active Profile" << std::endl;
        std::cout << "6. Initialize New Profile" << std::endl;
        std::cout << "7. Switch Active Profile" << std::endl;
        std::cout << "Enter your choice (1-7): ";
        std::cin >> customerChoice;

        switch (customerChoice) {
            case 1:
                // View active profile information
                DisplayInfo();
                break;
            case 2:
                // Modify active profile information
                ModifyProfile();
                break;
            case 3:
                // Check user permission
                CheckUserPermissionAccess();
                break;
            case 4:
                // Exit the program
                std::cout << "Exiting program..." << std::endl;
                return 0;
            case 5:
                // Delete active profile
                DeleteProfile();
                break;
            case 6: {
                // Initialize a new user profile
                std::string username;
                int age;
                std::string accessLevel;

                std::cout << "Enter username: ";
                std::cin >> username;
                std::cout << "Enter age: ";
                std::cin >> age;
                std::cout << "Enter access level (e.g., Admin, User): ";
                std::cin >> accessLevel;

                initializeProfile(username, age, accessLevel);
                break;
            }
            case 7:
                // Switch active user profile
                SwitchProfile();
                break;
            default:
                std::cout << "Invalid choice! Please enter a number between 1 and 7." << std::endl;
        }
    }

    return 0;
}

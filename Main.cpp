#include <iostream>
#include <string>
#include <vector>
#include <memory> // For std::unique_ptr
#include <new>
#include <limits>  // For std::numeric_limits

// added mehods for better stablity 
void displayMenu() {
    std::cout << "\n--- User Profile Menu ---\n"
              << "1. View Active Profile\n"
              << "2. Modify Active Profile\n"
              << "3. Check Permission\n"
              << "4. Exit\n"
              << "5. Delete Active Profile\n"
              << "6. Initialize New Profile\n"
              << "7. Switch Active Profile\n"
              << "Enter your choice (1-7): ";
}

int getValidChoice() {
    int choice;
    while (true) {
        std::cin >> choice;

        // Check if input is valid
        if (std::cin.fail() || choice < 1 || choice > 7) {
            std::cin.clear(); // Clear the error flag
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Discard invalid input
            std::cout << "Invalid choice. Please enter a number between 1 and 7: ";
        } else {
            // Valid input
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Clear buffer
            return choice;
        }
    }
}

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

void initializeProfile(const std::string &username, int age,
                       const std::string &accessLevel) {
  std::unique_ptr<UserProfile> newProfile =
      std::make_unique<UserProfile>(username, age, accessLevel);

  // Add the new profile to the vector
  userProfiles.push_back(std::move(newProfile));

  // Set the active profile to the newly created profile
  activeUserProfile = std::make_unique<UserProfile>(username, age, accessLevel);

  std::cout << "Profile for " << username << " is now active." << std::endl;
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

  std::cout << "Attempting to delete active profile: "
            << activeUserProfile->username << std::endl;

  // Validate that the active user profile's username is not empty
  if (activeUserProfile->username.empty()) {
    std::cout << "Error: Active user profile has an invalid username."
              << std::endl;
    return;
  }

  // Find the active profile in the vector and remove it
  for (auto it = userProfiles.begin(); it != userProfiles.end();) {
    if (*it && (*it)->username == activeUserProfile->username) {
      std::cout << "Found profile in the vector. Erasing now..." << std::endl;
      it = userProfiles.erase(it); // Correctly update iterator after erase

      activeUserProfile.reset(); // Reset the unique_ptr, releasing memory
      std::cout << "activeUserProfile has been reset." << std::endl;

      std::cout << "Active profile deleted successfully." << std::endl;
      return;
    } else {
      ++it;
    }
  }

  std::cout << "Profile not found in the vector." << std::endl;
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
  int choice=0;
  bool exitProgram = false;

  while (!exitProgram) {
    displayMenu();
    choice = getValidChoice();

    switch (choice) {
    case 1:
      std::cout << "Viewing Active Profile...\n";
      DisplayInfo();
      break;
    case 2:
      std::cout << "Modifying Active Profile...\n";
      ModifyProfile();
      break;
    case 3:
      std::cout << "Checking Permissions...\n";
      CheckUserPermissionAccess();
      break;
    case 4:
      std::cout << "Exiting...\n";
      exitProgram = true;
      break;
    case 5:
      std::cout << "Deleting Active Profile...\n";
      DeleteProfile();
      break;
    case 6:
      std::string username;
      int age;
      std::string accessLevel;
      std::cout << "Initializing New Profile...\n";
      std::cout << "Enter username: ";
      std::cin >> username;
      std::cout << "Enter age: ";
      std::cin >> age;
      std::cout << "Enter access level (e.g., Admin, User): ";
      std::cin >> accessLevel;
      initializeProfile(username, age, accessLevel);
      break;
    case 7:
      std::cout << "Switching Active Profile...\n";
      SwitchProfile();
      break;
    default:
      std::cout << "Invalid input. Please try again.\n";
      break;
    }
  }

  return 0;
}
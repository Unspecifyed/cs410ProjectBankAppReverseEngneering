#include <functional>
#include <iostream>
#include <limits>
#include <memory>
#include <string>
#include <vector>

struct UserProfile {
  std::string username;
  int age;
  std::string accessLevel;

  /// Construct a UserProfile object with the provided username, age, and access
  /// level.
  ///
  /// \param username The username of the user.
  /// \param age The age of the user.
  /// \param accessLevel The access level of the user.
  UserProfile(const std::string &username, int age,
              const std::string &accessLevel)
      : username(username), age(age), accessLevel(accessLevel) {}

  /// Displays the user profile information in a formatted manner.
  void display() const {
    std::cout << "Username: " << username << "\nAge: " << age
              << "\nAccess Level: " << accessLevel << std::endl;
  }
};

using ProfileList = std::vector<UserProfile>;

/// Displays the given function and prompts the user to enter a choice until a
/// valid choice is entered.
///
/// \param displayFn The function to display to the user.
///
/// \return A valid choice entered by the user.
int getValidChoice(std::function<void()> displayFn) {
  int choice;
  displayFn();
  while (true) {
    std::cin >> choice;
    if (std::cin.fail() || choice < 1 || choice > 7) {
      std::cin.clear();
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      std::cout << "Invalid choice. Please enter a number between 1 and 7: ";
      displayFn();
    } else {
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      return choice;
    }
  }
}

/// Displays the main menu to the user and prompts them to enter a choice.
/// The menu provides options to view the active profile, modify the active
/// profile, check the active profile's permission level, exit the program,
/// delete the active profile, initialize a new profile, or switch the active
/// profile. The function does not return a value.
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

/// Initializes a new profile with user input. The function prompts the user
/// to enter a username, age, and access level. The entered information is used
/// to construct a UserProfile object, which is then returned by the function.
///
/// \return A UserProfile object initialized with the user-provided information.
UserProfile initializeProfile() {
  std::string username;
  int age;
  std::string accessLevel;

  std::cout << "Initializing New Profile...\nEnter username: ";
  std::cin >> username;
  std::cout << "Enter age: ";
  std::cin >> age;
  std::cout << "Enter access level (e.g., Admin, User): ";
  std::cin >> accessLevel;

  return UserProfile(username, age, accessLevel);
}

/// Modifies the active profile with new values for username, age, and access
/// level. This function prompts the user to enter the new information.
///
/// \param activeProfile The active profile to modify.
void modifyProfile(UserProfile *activeProfile) {
  if (!activeProfile) {
    std::cout << "No active profile to modify." << std::endl;
    return;
  }

  std::cout << "Modifying Profile for: " << activeProfile->username
            << std::endl;

  std::cout << "Enter new username (current: " << activeProfile->username
            << "): ";
  std::string newUsername;
  std::cin >> newUsername;

  std::cout << "Enter new age (current: " << activeProfile->age << "): ";
  int newAge;
  std::cin >> newAge;

  std::cout << "Enter new access level (current: " << activeProfile->accessLevel
            << "): ";
  std::string newAccessLevel;
  std::cin >> newAccessLevel;

  // Update profile details
  activeProfile->username = newUsername;
  activeProfile->age = newAge;
  activeProfile->accessLevel = newAccessLevel;

  std::cout << "Profile updated successfully." << std::endl;
}

/// Checks the permissions of the active profile based on their access level.
/// If the profile has an Admin access level, they are granted full permissions.
/// Otherwise, they have limited permissions.
///
/// \param activeProfile The active profile whose permissions are checked.
void checkPermissions(const UserProfile *activeProfile) {
  if (!activeProfile) {
    std::cout << "No active profile to check permissions for." << std::endl;
    return;
  }

  std::cout << "Checking permissions for: " << activeProfile->username
            << std::endl;

  if (activeProfile->accessLevel == "Admin") {
    std::cout << "Access Level: Admin. You have full permissions." << std::endl;
  } else if (activeProfile->accessLevel == "User") {
    std::cout << "Access Level: User. You have limited permissions."
              << std::endl;
  } else {
    std::cout << "Access Level: " << activeProfile->accessLevel
              << ". Permissions are restricted." << std::endl;
  }
}

/// Deletes the active profile by removing it from the list of profiles and
/// setting the active profile pointer to nullptr.
///
/// \param profiles The list of user profiles.
/// \param activeProfile The currently active profile pointer, which will be set
/// to nullptr after deletion. \return The updated list of profiles after the
/// active profile has been removed.
ProfileList deleteActiveProfile(ProfileList profiles,
                                UserProfile *&activeProfile) {
  if (!activeProfile) {
    std::cout << "No active profile to delete." << std::endl;
    return profiles;
  }

  std::cout << "Deleting active profile: " << activeProfile->username
            << std::endl;

  // Find and remove the active profile from the profiles list
  profiles.erase(std::remove_if(profiles.begin(), profiles.end(),
                                [&](const UserProfile &profile) {
                                  return profile.username ==
                                         activeProfile->username;
                                }),
                 profiles.end());

  // Set active profile to nullptr
  activeProfile = nullptr;

  std::cout << "Profile deleted successfully." << std::endl;
  return profiles;
}

/// Switches the active profile by displaying the list of available profiles and
/// allowing the user to choose one by username.
///
/// \param profiles The list of user profiles.
/// \param activeProfile The currently active profile pointer, which will be
/// updated to the selected profile.
void switchActiveProfile(ProfileList &profiles, UserProfile *&activeProfile) {
  if (profiles.empty()) {
    std::cout << "No profiles available to switch to." << std::endl;
    return;
  }

  std::cout << "Available Profiles:" << std::endl;
  for (const auto &profile : profiles) {
    std::cout << " - " << profile.username << std::endl;
  }

  std::string username;
  std::cout << "Enter the username of the profile you want to switch to: ";
  std::cin >> username;

  // Search for the profile with the matching username
  for (auto &profile : profiles) {
    if (profile.username == username) {
      activeProfile = &profile;
      std::cout << "Switched to profile: " << activeProfile->username
                << std::endl;
      return;
    }
  }

  // If no matching username is found
  std::cout << "Profile with username \"" << username << "\" not found."
            << std::endl;
}

/// Handles the given menu selection by either displaying the active profile,
/// modifying the active profile, checking the active profile's permission
/// level, exiting the program, deleting the active profile, initializing a
/// new profile, switching the active profile, or displaying an error message.
///
/// \param choice The menu selection entered by the user.
/// \param profiles The list of user profiles.
/// \param activeProfile The currently active profile.
/// \param exitProgram A boolean indicating whether the program should exit.
///
/// \return The list of user profiles, potentially modified to include a new
/// profile.
ProfileList handleMenuSelection(int choice, ProfileList profiles,
                                UserProfile *&activeProfile,
                                bool &exitProgram) {
  switch (choice) {
  case 1:
    if (activeProfile) {
      activeProfile->display();
    } else {
      std::cout << "No active profile to view." << std::endl;
    }
    break;
  case 2:
    modifyProfile(activeProfile); // Modify the active profile
    break;
  case 3:
    checkPermissions(activeProfile); // Check permissions of the active profile
    break;
  case 4:
    std::cout << "Exiting..." << std::endl;
    exitProgram = true;
    break;
  case 5:
    profiles = deleteActiveProfile(profiles,
                                   activeProfile); // Delete the active profile
    break;
  case 6:
    profiles.push_back(initializeProfile());
    break;
  case 7:
    switchActiveProfile(profiles, activeProfile); // Switch the active profile
    break;
  default:
    std::cout << "Invalid input. Please try again." << std::endl;
    break;
  }
  return profiles;
}

/**
 * @brief The main entry point of the program
 *
 * This function initializes all state and enters the main loop, where it
 * repeatedly displays the menu and handles the user's selection.
 *
 * @return 0 on successful exit
 */
int main() {
  ProfileList profiles;
  UserProfile *activeProfile = nullptr; // Actively selected profile
  bool exitProgram = false;

  while (!exitProgram) {
    int choice = getValidChoice(displayMenu);
    profiles =
        handleMenuSelection(choice, profiles, activeProfile, exitProgram);
  }
  return 0;
}

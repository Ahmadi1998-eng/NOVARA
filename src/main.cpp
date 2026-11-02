#include <iostream>
#include <string>
#include <vector>
#include <limits>
#include <cctype>


using namespace std;

struct User
{
string fullName;
string email;
string phone;
string password;

};
bool emailExists(const vector<User>& users, const string& email, int currentUserIndex)
{
    for (size_t i = 0; i < users.size(); i++)
    {
        if (static_cast<int>(i) != currentUserIndex &&
            users[i].email == email)
        {
            return true;
        }
    }

    return false;
}
bool isValidEmail(const string& email)
{
    size_t at = email.find('@');

    if (at == string::npos || at == 0)
    {
        return false;
    }

    size_t dot = email.find('.', at);

    if (dot == string::npos || dot == at + 1 || dot == email.length() - 1)
    {
        return false;
    }

    return true;
}
bool normalizePhone(string& phone)
{
    string cleaned = "";

    
    for (char ch : phone)
    {
        if (ch != ' ' && ch != '-')
        {
            cleaned += ch;
        }
    }

    if (cleaned.substr(0, 2) == "00")
    {
        cleaned = "+" + cleaned.substr(2);
    }

    
    if (cleaned.empty() || cleaned[0] != '+')
    {
        return false;
    }

    
    string digits = cleaned.substr(1);

    if (digits.empty() || digits.length() > 15)
    {
        return false;
    }

    for (char ch : digits)
    {
        if (!isdigit(static_cast<unsigned char>(ch)))
        {
            return false;
        }
    }

    
    phone = cleaned;

    return true;
    }
bool phoneExists(const vector<User>& users, const string& phone, int currentUserIndex)
{
    for (size_t i = 0; i < users.size(); i++)
    {
        if (static_cast<int>(i) != currentUserIndex &&
            users[i].phone == phone)
        {
            return true;
        }
    }

    return false;
}
bool isValidPassword(const string& password)
{
    bool hasLetter = false;
    bool hasDigit = false;

    for (char ch : password)
    {
        if (isalpha(static_cast<unsigned char>(ch)))
        {
            hasLetter = true;
        }

        if (isdigit(static_cast<unsigned char>(ch)))
        {
            hasDigit = true;
        }
    }

    return password.length() >= 8 && hasLetter && hasDigit;
}
int loginUser(const vector<User>& users)
{
    string identifier;
    string password;

    cout << "\n--- User Login ---\n";

    cout << "Enter your email or phone number: ";
    getline(cin, identifier);

    cout << "Enter your password: ";
    getline(cin, password);

    for (size_t i = 0; i < users.size(); i++)
    {
        if (users[i].email == identifier || users[i].phone == identifier)
        {
            if (users[i].password == password)
            {
                cout << "\nWelcome back to NOVARA!\n";
                cout << "Login successful.\n";

                return static_cast < int > (i) ;
            }
            else
            {
                cout << "\nError: Incorrect password!\n";

                return -1;
            }
        }
    }

    cout << "\nError: Account not found!\n";

    return -1;
}
void editProfile(vector<User>& users, int userIndex)
{
    string newName;
    string newEmail;
    string newPhone;

    cout << "\n--- Edit My Profile ---\n";

    cout << "Enter new full name: ";
    getline(cin, newName);

    if (newName.empty())
    {
        cout << "\nError: Full name cannot be empty!\n";
        return;
    }

    cout << "Enter new email: ";
    getline(cin, newEmail);

    if (!isValidEmail(newEmail))
    {
        cout << "\nError: Invalid email address!\n";
        return;
    }

    if (emailExists(users, newEmail, userIndex))
    {
        cout << "\nError: This email is already registered!\n";
        return;
    }

    cout << "Enter new phone number: ";
    getline(cin, newPhone);

    if (!normalizePhone(newPhone))
    {
        cout << "\nError: Invalid phone number!\n";
        return;
    }

    if (phoneExists(users, newPhone, userIndex))
    {
        cout << "\nError: This phone number is already registered!\n";
        return;
    }

    users[userIndex].fullName = newName;
    users[userIndex].email = newEmail;
    users[userIndex].phone = newPhone;

    cout << "\nProfile updated successfully!\n";
}
void changePassword(vector<User>& users, int userIndex)
{
    string currentPassword;
    string newPassword;
    string confirmPassword;

    cout << "\n--- Change Password ---\n";


    cout << "Enter current password: ";
    getline(cin, currentPassword);

    if (currentPassword != users[userIndex].password)
    {
        cout << "\nError: Current password is incorrect!\n";
        return;
    }

    cout << "Enter new password: ";
    getline(cin, newPassword);

    if (!isValidPassword(newPassword))
    {
        cout << "\nError: Password must contain at least 8 characters, including letters and numbers!\n";
        return;
    }

    cout << "Confirm new password: ";
    getline(cin, confirmPassword);


    if (newPassword != confirmPassword)
    {
        cout << "\nError: Passwords do not match!\n";
        return;
    }

    users[userIndex].password = newPassword;

    cout << "\nPassword changed successfully!\n";
}
void userDashboard(vector<User>& users, int userIndex)
{
    int choice;

    while (true)
    {
        cout << "\n======================\n";
        cout << "     NOVARA USER PANEL\n";
        cout << "======================\n";

        cout << "Welcome, " << users[userIndex].fullName << "!\n";

        cout << "\n1. View My Profile\n";
        cout << "2. Edit My Profile\n";
        cout<<"3. Edit Password\n";
        cout << "4. Logout\n";

        cout << "\nChoose an option: ";

        cin >> choice;

        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        switch (choice)
        {
        case 1:

            cout << "\n--- My Profile ---\n";

            cout << "Full Name: " << users[userIndex].fullName << endl;
            cout << "Email: " << users[userIndex].email << endl;
            cout << "Phone: " << users[userIndex].phone << endl;

            break;

        case 2:

            editProfile(users, userIndex);

            break;

      case 3:

    changePassword(users, userIndex);

    break;

case 4:

    cout << "\nYou have successfully logged out!\n";

    return;

        default:

            cout << "\nInvalid option! Try again.\n";
        }
    }
}

void registerUser(vector<User>& users){
    User newUser;
        cout<<"\n--- User Registration---\n";

        cout<<"Enter your full name\n";
        getline(cin, newUser.fullName);

    if(newUser.fullName.empty()){
        cout<<"\nError : Full name cannot be empty!\n";
            return;
    }

        cout<<"Enter your Email\n";
        getline(cin, newUser. email);
if (!isValidEmail(newUser.email))
{
    cout << "\nInvalid email address!\n";
    return;
}

if (emailExists(users, newUser.email, -1))
{
    cout << "\nThis email is already registered!\n";
    return;
}

        cout<<"Enter your phone number\n";
        getline(cin, newUser.phone);

    if (!normalizePhone(newUser.phone))
    {
        cout<<"\nInvalid international phone number!\n";
            return;
    }
    if (phoneExists(users, newUser.phone, -1)){

        cout<<"\nThis phone number is already registered!\n";
            return;
    }

        cout<<"Enter your password\n";
        getline(cin, newUser.password);

if (!isValidPassword(newUser.password))
{
    cout << "\nError: Password must contain at least 8 characters, including letters and numbers!\n";
    return;
}
        users.push_back(newUser);

        cout<<"\n Registration completed successfully!\n";


}

int main()
{
    vector<User> users;

    int choice;

    while (true)
    {
        cout << "\n===========================\n";
        cout << "     WELCOME TO NOVARA\n";
        cout << "===========================\n";

        cout << "1. Register\n";
        cout << "2. Login\n";
        cout << "3. Exit\n";

        cout << "\nChoose an option: ";

        cin >> choice;

        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        switch (choice)
        {
            case 1:

                registerUser(users);

                break;

            case 2:
            {
                int userIndex = loginUser(users);

                if (userIndex != -1)
                {
                    userDashboard(users, userIndex);
                }

                break;
            }

            case 3:

                cout << "Thank you for using NOVARA!\n";

                return 0;

            default:

                cout << "Invalid option! Try again.\n";
        }
    }

    return 0;
}
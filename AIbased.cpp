#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <cctype>
#include <vector>
using namespace std;

class temp {
    string user_name, password, EMail;
    string searchName, searchPassword, searchEmail;
    fstream file;

    bool isPasswordStrong(const string& pwd);
    string suggestUserName(const string& baseName);
   

public:
    void login();
    void signUp();
    void forgot();
     void aiChat();
} obj;

string trim(const string& str) {
    size_t first = str.find_first_not_of(" ");
    size_t last = str.find_last_not_of(" ");
    return str.substr(first, (last - first + 1));
}

bool temp::isPasswordStrong(const string& pwd) {
    bool hasUpper = false, hasLower = false, hasDigit = false, hasSpecial = false;
    string specialChars = "!@#$%^&*()-_+=<>?/|{}[]";

    if (pwd.length() < 8) {
        return false;
    }

    for (char ch : pwd) {
        if (isupper(ch)) hasUpper = true;
        if (islower(ch)) hasLower = true;
        if (isdigit(ch)) hasDigit = true;
        if (specialChars.find(ch) != string::npos) hasSpecial = true;
    }

    return hasUpper && hasLower && hasDigit && hasSpecial;
}

string temp::suggestUserName(const string& baseName) {
    vector<string> suggestions;
    for (int i = 1; i <= 5; ++i) {
        suggestions.push_back(baseName + to_string(i));
    }

    cout << "\nThe username \"" << baseName << "\" is taken. Here are some suggestions:\n";
    for (const string& suggestion : suggestions) {
        cout << "- " << suggestion << endl;
    }

    return suggestions[0];
}

void temp::aiChat() {
    string input;
    cout << "\nWelcome to AI Chat! Type 'exit' to return to the menu.";
    while (true) {
        cout << "\nYou: ";
        getline(cin, input);
        if (input == "exit") {
            cout << "Exiting AI Chat...\n";
            break;
        } else if (input.find("hello") != string::npos || input.find("hi") != string::npos) {
            cout << "AI: Hello! How can I help you today?";
        } else if (input.find("password") != string::npos) {
            cout << "AI: I can help you create a strong password. Make sure it has at least 8 characters, including uppercase, lowercase, digits, and special symbols.";
        } else {
            cout << "AI: I'm not sure how to respond to that. Try asking about passwords!";
        }
    }
}

void temp::signUp() {
    cin.ignore(); 
    cout << "\n---------SIGN-UP----------";
    cout << "\nEnter the User_name: ";
    getline(cin, user_name);

    file.open("loginData.txt", ios::in);
    string line;
    bool userExists = false;
    while (getline(file, line)) {
        stringstream ss(line);
        string existingUser;
        getline(ss, existingUser, '*');
        existingUser = trim(existingUser);
        if (existingUser == user_name) {
            userExists = true;
            break;
        }
    }
    file.close();

    if (userExists) {
        user_name = suggestUserName(user_name);
    }

    cout << "Enter the E-Mail Address: ";
    getline(cin, EMail);

    cout << "Enter your Password: ";
    getline(cin, password);

    if (!isPasswordStrong(password)) {
        cout << "\nYour password is weak! It should be at least 8 characters long and contain uppercase, lowercase, digits, and special symbols.\n";
        cout << "Please enter a stronger password: ";
        getline(cin, password);
    }

    file.open("loginData.txt", ios::out | ios::app);
    file << user_name << " * " << EMail << " * " << password << endl;
    file.close();

    cout << "\nAccount successfully created!\n";
}

void temp::login() {
    cin.ignore();
    cout << "\n---------LOGIN----------";
    cout << "\nEnter Your User_Name: ";
    getline(cin, searchName);
    cout << "Enter the Password: ";
    getline(cin, searchPassword);

    file.open("loginData.txt", ios::in);

    bool found = false;
    string line;

    while (getline(file, line)) {
        stringstream ss(line);
        getline(ss, user_name, '*');
        getline(ss, EMail, '*');
        getline(ss, password);

        user_name = trim(user_name);
        EMail = trim(EMail);
        password = trim(password);

        if (user_name == searchName && password == searchPassword) {
            cout << "\nAccount Login Successful!";
            cout << "\nWelcome, " << user_name << "!";
            found = true;
            break;
        }
    }

    if (!found) {
        cout << "\nInvalid Username or Password.";
    }

    file.close();
}

void temp::forgot() {
    cin.ignore();
    cout << "\n---------FORGOT PASSWORD----------";
    cout << "\nEnter Your User_Name: ";
    getline(cin, searchName);
    cout << "Enter Your E-Mail: ";
    getline(cin, searchEmail);

    file.open("loginData.txt", ios::in);

    bool found = false;
    string line;

    while (getline(file, line)) {
        stringstream ss(line);
        getline(ss, user_name, '*');
        getline(ss, EMail, '*');
        getline(ss, password);

        user_name = trim(user_name);
        EMail = trim(EMail);
        password = trim(password);

        if (user_name == searchName && EMail == searchEmail) {
            cout << "\nAccount Found!";
            cout << "\nYour Password: " << password;
            found = true;
            break;
        }
    }

    if (!found) {
        cout << "\nAccount not found. Please check your details.";
    }

    file.close();
}

int main() {
    char choice;
    do {
        cout << "\n---------MENU---------";
        cout << "\n1 - Login";
        cout << "\n2 - Sign-Up";
        cout << "\n3 - Forgot Password";
        cout << "\n4 - AI Chat";
        cout << "\n5 - Exit";
        cout << "\nEnter Your Choice: ";
        cin >> choice;

        switch (choice) {
            case '1':
                obj.login();
                break;
            case '2':
                obj.signUp();
                break;
            case '3':
                obj.forgot();
                break;
            case '4':
                cin.ignore();
                obj.aiChat();
                break;
            case '5':
                cout << "\nExiting the program. Goodbye!\n";
                break;
            default:
                cout << "\nInvalid Selection. Please try again.";
        }
    } while (choice != '5');

    return 0;
}

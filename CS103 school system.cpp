#include <iostream>
#include <windows.h>
#include <string>
#include <vector>
#include <iomanip>
#include <sstream>
#include <filesystem>
#include <fstream>
#include <utility>
#include <cstdlib>
#include <map>
#include <filesystem>

using namespace std;

bool isaccess = false;
bool isAdmin = false;
string current_user = "";
double globalTotalPrice = 0.0; // Global variable to store the total price of all food choices

vector<pair<string, vector<string>>> read_csv(string filename) {
    ifstream file(filename);
    vector<pair<string, vector<string>>> result;
    string line;
    string cell;
    vector<string> values;
    while (getline(file, line)) {
        stringstream lineStream(line);
        while (getline(lineStream, cell, ',')) {
            values.push_back(cell);
        }
        result.push_back(make_pair(values.at(0), values));
        values.clear();
    }
    return result;
}

//will check for a number use instead of cin
int validInput()
{
    int x;
    cin >> x;
    while (cin.fail())
    {
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "Bad entry.  Enter a NUMBER: ";
        cin >> x;
    }
    cout << endl;
    return x;
}

// Function to apply discount
double applyDiscount(double total) {
    string discount_code;
    cout << "If you have a discount code, please enter it now (Press enter to skip): ";
    cin.ignore(); // To clear the newline character from the input buffer
    getline(cin, discount_code);

    if (discount_code == "SIGMA15") {
        total *= 0.85;
        cout << "Discount applied! You get 15% off.\n";
    }
    else if (!discount_code.empty()) {
        cout << "Invalid discount code.\n";
    }

    return total;
}

void weekly_menu() {
    if (!isaccess) {
        cout << "You must be logged in to access the weekly menu.\n";
        Sleep(3000);
        system("CLS");
        return;
    }

    int day_choice;
    string day;
    cout << "Please choose a day of the week for your order:" << endl;

    while (true) {
        cout << endl;
        cout << "1. Monday" << endl;
        cout << "2. Tuesday" << endl;
        cout << "3. Wednesday" << endl;
        cout << "4. Thursday" << endl;
        cout << "5. Friday" << endl;

        cout << "\nPlease enter your choice: ";
        cin >> day_choice;

        if (day_choice < 1 || day_choice > 5) {
            cout << "Please enter a number between 1 and 5\n";
            Sleep(2000);
            system("CLS");
            continue;
        }

        switch (day_choice) {
        case 1: day = "Monday"; break;
        case 2: day = "Tuesday"; break;
        case 3: day = "Wednesday"; break;
        case 4: day = "Thursday"; break;
        case 5: day = "Friday"; break;
        }
        cout << "You chose " << day << endl;
        break;
    }

    vector<pair<string, vector<string>>> result = read_csv("Order.csv");
    for (const auto& entry : result) {
        if (entry.first == day) {
            cout << "You've already chosen " << day << ".\n";
            Sleep(3000);
            system("CLS");
            return;
        }
    }

    map<string, int> menu = {
        {"Burger", 12},
        {"Cake", 7},
        {"Pizza", 10},
        {"Soda", 4}
    };

    cout << endl;
    cout << "Weekly menu:\n";

    string order;
    int total = 0;
    while (true) {
        int n = 1;
        for (const auto& pair : menu) {
            cout << n++ << ". " << pair.first << " $" << pair.second << endl;
        }

        int food_choice;
        cout << "\nPlease enter your choice 1-4: ";
        cin >> food_choice;

        if (food_choice < 1 || food_choice > 4) {
            cout << "Please enter a number between 1 and 4\n";
            Sleep(2000);
            system("CLS");
            return;
        }

        switch (food_choice) {
        case 1: order = "Burger"; total += 12; break;
        case 2: order = "Cake"; total += 7; break;
        case 3: order = "Pizza"; total += 10; break;
        case 4: order = "Soda"; total += 4; break;
        }
        cout << "You ordered a " << order << endl;
        break;
    }

    // Apply discount if any
    total = applyDiscount(total);  

    // Update the global total price
    globalTotalPrice += total; 

    // Open the file in append mode
    ofstream outFile("Order.csv", ios::app);
    if (!outFile) {
        cerr << "Error opening file for writing\n";
        return;
    }

    // Write user information to the file
    outFile << day << "," << order << "," << total << "\n"; 

    // Close the file
    outFile.close();

    // Confirmation message
    cout << "Order successful! Your total is $" << total << endl; 
    Sleep(3000);
    system("CLS");

    while (true) {
        cout << "Do you want to choose another food item/day? (y/n): ";
        string y_or_n;
        cin >> y_or_n;

        for (char& c : y_or_n) {
            c = tolower(c);
        }

        if (y_or_n == "y") {
            weekly_menu();
            return;
        }
        else if (y_or_n == "n") {
            break;
        }
        else {
            cout << "Please input the letter y or n" << endl;
            continue;
        }
    }

    system("CLS");
    return;
}

void details() {
    // Information about the school/office. also about locations and addresses also phone numbers of the office workers etc...
    cout << "Welcome to the information menu" << endl;

    int info_choice;
    while (true) {

        cout << "\n1. office location" << endl;
        cout << "2. office phone numbers" << endl;
        cout << "3. where to pick up the ordered food" << endl;
        cout << "4. return to main menu" << endl;

        cout << "\nplease enter your choice 1-4: ";
        cin >> info_choice;
        if (info_choice > 4 or info_choice < 0) {
            cout << "please enter a number between 1 and 4\n";
            Sleep(2000);
            system("CLS");
            return;
        }

        if (info_choice == 1) {
            cin.clear();
            cout << "The office location is 8008 Lane, up the driveway then you will reach Saint Ignatius Grammar Marist Academy" << endl;
            Sleep(3500);
            system("CLS");
            continue;
        }
        else if (info_choice == 2) {
            cin.clear();
            cout << "Main office phone number: 04106122" << endl;
            cout << "Vice principle phone number: 42069101" << endl;
            Sleep(4000);
            system("CLS");
            continue;
        }
        else if (info_choice == 3) {
            cin.clear();
            cout << "once you order your food and get a confirmation the food will be delivered to you in class" << endl;
            cout << "if you have any more questions contact the main office" << endl;
            Sleep(5000);
            system("CLS");
            continue;
        }
        else if (info_choice == 4) {
            cin.clear();
            system("CLS");
            return;
        }
        else {
            validInput();
            continue;
        }
        break;
    }
}


void registerUser() {
    string reg_username, reg_password;
    char admin_access;
    string ADM = "";

    cout << "Enter username: ";
    cin.ignore(1000, '\n');
    cin.clear();
    getline(cin, reg_username);

    // Checking to make sure the currently entered username doesn't already exist
    vector<pair<string, vector<string>>> result = read_csv("Accounts.csv");
    for (const auto& entry : result) {
        if (entry.first == reg_username) {
            cout << "Username " << reg_username << " already exists";
            Sleep(3000);
            system("CLS");
            return;
        }
    }

    // Getting password from the user
    cout << "Enter password: ";
    getline(cin, admin_access);

    // Open the file in append mode
    ofstream outFile("Accounts.csv", ios::app);
    if (!outFile) {
        cerr << "Error opening file for writing\n";
        return;
    }

    // Asking the user if they would like admin access
    ADM = "0";
    while (true) {
        cout << "Would you like to give this account admin access (y/n): ";
        cin >> admin_access;
        if (admin_access == 'Y' || admin_access == 'y') {
            ADM = "1";
            break;
        }
        else if (admin_access == 'N' || admin_access == 'n') {
            ADM = "0";
            break;
        }
        else {
            cout << "Invalid option";
        }
    }

    // Write user information to the file
    outFile << reg_username << "," << reg_password << "," << ADM << "\n";

    // Close the file
    outFile.close();

    // Confirmation message
    cout << "User registration successful\n";
    Sleep(3000);
    system("CLS");
}

void login() {
    string username, password;
    cin.ignore(1000, '\n');
    cin.clear();
    cout << "Enter username: ";
    getline(cin, username);
    cout << "Enter password: ";
    getline(cin, password);

    vector<pair<string, vector<string>>> result = read_csv("Accounts.csv");
    string actual_username = "", actual_password = "", actual_admin = "";
    for (const auto& entry : result) {
        if (entry.first == username) {
            actual_username = entry.first;
            actual_password = entry.second.at(1);
            actual_admin = entry.second.at(2);
        }
    }

    if (username == actual_username && password == actual_password) {
        cout << "Login successful" << endl;
        current_user = username;
        isaccess = true;
        if (actual_admin == "1") {
            isAdmin = true;
            cout << "Admin access granted";
        }
        Sleep(3000);
        system("CLS");
    }
    else {
        cout << "Login failed" << endl;
        Sleep(3000);
        system("CLS");
    }
}

void accoutManage() {
    int accoutn_manage_option;
    while (true) {
        cout << "Login/Registration" << endl;
        cout << "\n";
        cout << "1: Login" << endl;
        cout << "2: Create account" << endl;
        cout << "3: Log out" << endl;
        cout << "4: Exit" << endl;
        cout << "Please enter your choice: ";
        cin >> accoutn_manage_option;

        switch (accoutn_manage_option) {
        case 1:
            if (!isaccess) {
                system("CLS");
                login();
            }
            else {
                cout << "Already logged in";
                Sleep(3000);
                system("CLS");
            }
            break;

        case 2:
            registerUser();
            isaccess = true;
            break;

        case 3:
            if (isaccess) {
                cout << "Logged out";
                isaccess = false;
                Sleep(3000);
                system("CLS");
            }
            else {
                cout << "Not currently signed in";
                Sleep(3000);
                system("CLS");
            }
            break;

        case 4:
            system("CLS");
            return;

        default:
            cout << "Invalid input";
            break;
        }
    }
}

void printReceiptAndCredentials() {
    cout << "User: " << current_user << endl;

    vector<pair<string, vector<string>>> accounts = read_csv("Accounts.csv");
    vector<pair<string, vector<string>>> orders = read_csv("Order.csv");

    cout << "\nAccounts:\n";
    for (const auto& account : accounts) {
        for (const auto& field : account.second) {
            cout << field << " ";
        }
        cout << endl;
    }

    cout << "\nOrders:\n";
    for (const auto& order : orders) {
        for (const auto& field : order.second) {
            cout << field << " ";
        }
        cout << endl;
    }

    // Print the total price of all orders
    cout << "\nTotal price of all orders: $" << fixed << setprecision(2) << globalTotalPrice << endl; 
}

int main() {
    cout << "Welcome to the school lunch ordering system! \n";
    cout << endl;

    while (true) {
        cout << "1. Weekly menu \n";
        cout << "2. Contact details and office locations \n";
        cout << "3. Login and registration\n";
        cout << "4. Quit \n";

        cout << "\nPlease enter your choice: ";
        int menu_choice;
        cin >> menu_choice;

        if (menu_choice < 1 || menu_choice > 4) {
            cout << "Please enter a number between 1 and 4\n";
            Sleep(1500);
            system("CLS");
            continue;
        }

        switch (menu_choice) {
        case 1:
            system("CLS");
            weekly_menu();
            break;
        case 2:
            system("CLS");
            details();
            break;
        case 3:
            system("CLS");
            accoutManage();
            break;
        case 4:
            system("CLS");
            printReceiptAndCredentials();
            Sleep(7000);
            system("CLS");
            exit(0);
        }
    }
}

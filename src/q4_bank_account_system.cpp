// ----------------------------------------------------------------------------
// Question 4: Bank Account Management System
// A menu-driven program to create an account, deposit, withdraw, check the
// balance and display the account details.
//
// Bank rules enforced:
//   * the initial deposit must be greater than 0
//   * deposits must be greater than 0
//   * withdrawals must be greater than 0 and cannot exceed the balance
// ----------------------------------------------------------------------------
#include <iomanip>
#include <iostream>
#include <string>

#include "input_utils.h"

using namespace std;

// ---- Function prototypes (signatures as required by the brief) -----------------
void createAccount(string& name, int& accountNumber, double& balance);
void depositMoney(double& balance);
void withdrawMoney(double& balance);
void checkBalance(const double& balance);
void displayAccountDetails(const string& name, const int& accountNumber, const double& balance);
void displayMenu();

int main() {
    string name;
    int accountNumber = 0;
    double balance = 0.0;
    bool accountCreated = false;
    int choice = 0;

    do {
        displayMenu();
        choice = input::readInt("Enter your choice (1-6): ", 1, 6);

        // Every option except "Create" and "Exit" needs an account first
        if (choice >= 2 && choice <= 5 && !accountCreated) {
            cout << "Please create an account first (option 1).\n";
            continue;
        }

        switch (choice) {
        case 1:
            // Protect an existing account from being overwritten by accident
            if (accountCreated &&
                !input::readYesNo("An account already exists and will be replaced. Continue? (y/n): ")) {
                break;
            }
            createAccount(name, accountNumber, balance);
            accountCreated = true;
            break;
        case 2:
            depositMoney(balance);
            break;
        case 3:
            withdrawMoney(balance);
            break;
        case 4:
            checkBalance(balance);
            break;
        case 5:
            displayAccountDetails(name, accountNumber, balance);
            break;
        case 6:
            cout << "Exiting the system. Goodbye!\n";
            break;
        }
    } while (choice != 6);

    return 0;
}

void displayMenu() {
    cout << "\n--- Bank Account Management System ---\n"
         << "1. Create Account\n"
         << "2. Deposit Money\n"
         << "3. Withdraw Money\n"
         << "4. Check Balance\n"
         << "5. Display Account Details\n"
         << "6. Exit\n";
}

// Prompts for the name, account number and an initial deposit greater than 0.
void createAccount(string& name, int& accountNumber, double& balance) {
    name = input::readNonEmpty("Enter your name: ");
    accountNumber = input::readInt("Enter your account number: ", 1, 999999999);
    balance = input::readPositiveDouble("Enter your initial deposit (must be greater than 0): R");
    cout << "Account created successfully!\n";
}

// The deposit must be greater than 0 (readPositiveDouble keeps asking until it is).
void depositMoney(double& balance) {
    const double deposit = input::readPositiveDouble("Enter amount to deposit: R");
    balance += deposit;
    cout << fixed << setprecision(2);
    cout << "Amount deposited successfully. New balance: R" << balance << "\n";
}

// The withdrawal must be greater than 0 and no more than the current balance.
void withdrawMoney(double& balance) {
    const double withdrawal = input::readPositiveDouble("Enter amount to withdraw: R");
    cout << fixed << setprecision(2);
    if (withdrawal > balance) {
        cout << "Insufficient funds. Current balance: R" << balance << "\n";
    } else {
        balance -= withdrawal;
        cout << "Amount withdrawn successfully. New balance: R" << balance << "\n";
    }
}

void checkBalance(const double& balance) {
    cout << fixed << setprecision(2);
    cout << "Current balance: R" << balance << "\n";
}

void displayAccountDetails(const string& name, const int& accountNumber, const double& balance) {
    cout << fixed << setprecision(2);
    cout << "\n--- Account Details ---\n"
         << "Account Holder: " << name << "\n"
         << "Account Number: " << accountNumber << "\n"
         << "Current Balance: R" << balance << "\n";
}

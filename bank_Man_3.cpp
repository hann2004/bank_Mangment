#include <iostream>
#include <string>
#include <limits>
using namespace std;

// Base Account class
class Account {
protected:
    long accountNumber;
    string holderName;
    double balance;
    string accountType;

public:
    Account(long accNumber, string name, double initialBalance, string type) {
        accountNumber = accNumber;
        holderName = name;
        balance = initialBalance;
        accountType = type;
    }

    virtual void deposit(double amount) {
        balance += amount;
        cout << "\nDeposit successful. New balance: " << balance << endl;
    }

    virtual void withdraw(double amount) {
        if (balance >= amount) {
            balance -= amount;
            cout << "\nWithdrawal successful. New balance: " << balance << endl;
        } else {
            cout << "\nInsufficient funds!" << endl;
        }
    }

    virtual void displayDetails() const {
        cout << "\nAccount Number: " << accountNumber << endl;
        cout << "Account Holder: " << holderName << endl;
        cout << "Account Type: " << accountType << endl;
        cout << "Balance: " << balance << endl;
    }

    long getAccountNumber() const {
        return accountNumber;
    }

    string getHolderName() const {
        return holderName;
    }
};

// Derived class: SavingsAccount
class SavingsAccount : public Account {
public:
    SavingsAccount(long accNumber, string name, double initialBalance)
        : Account(accNumber, name, initialBalance, "Savings") {}

    void withdraw(double amount) override {
        if (balance - amount < 500) { // Maintain a minimum balance of 500
            cout << "\nCannot withdraw. Minimum balance of 500 required!" << endl;
        } else {
            Account::withdraw(amount);
        }
    }
};

// Derived class: BusinessAccount
class BusinessAccount : public Account {
public:
    BusinessAccount(long accNumber, string name, double initialBalance)
        : Account(accNumber, name, initialBalance, "Business") {}

    void withdraw(double amount) override {
        if (balance - amount < 1000) {
            cout << "\nCannot withdraw. Minimum balance of 1000 required!" << endl;
        } else {
            Account::withdraw(amount);
        }
    }

    void deposit(double amount) override {
        balance += amount + (amount * 0.01);
        cout << "\nDeposit successful with a 1% bonus. New balance: " << balance << endl;
    }
};

// Derived class: EducationalAccount
class EducationalAccount : public Account {
public:
    EducationalAccount(long accNumber, string name, double initialBalance)
        : Account(accNumber, name, initialBalance, "Educational") {}

    void withdraw(double amount) override {
        if (amount > 500) {
            cout << "\nCannot withdraw more than 500 in a single transaction!" << endl;
        } else if (balance >= amount) {
            balance -= amount;
            cout << "\nWithdrawal successful. New balance: " << balance << endl;
        } else {
            cout << "\nInsufficient funds!" << endl;
        }
    }
};

// Bank class
class Bank {
private:
    static const int MAX_ACCOUNTS = 1000;
    Account* accounts[MAX_ACCOUNTS];
    int accountCount;

    int findAccountIndex(long accountNumber) {
        for (int i = 0; i < accountCount; ++i) {
            if (accounts[i]->getAccountNumber() == accountNumber) {
                return i;
            }
        }
        return -1;
    }

public:
    Bank() : accountCount(0) {
        accounts[accountCount++] = new SavingsAccount(10001, "Usman Zewude", 10000);
        accounts[accountCount++] = new BusinessAccount(10002, "Rewuda Hussen", 23000);
        accounts[accountCount++] = new EducationalAccount(10003, "Hanan Nasir", 15000);
        accounts[accountCount++] = new SavingsAccount(10004, "Eba Mulgeta", 1500);
        accounts[accountCount++] = new BusinessAccount(10005, "Abebe Teferi", 8000);
    }

    ~Bank() {
        for (int i = 0; i < accountCount; i++) {
            delete accounts[i];
        }
    }

    void createAccount() {
        if (accountCount >= MAX_ACCOUNTS) {
            cout << "Maximum account limit reached. Cannot create more accounts!" << endl;
            return;
        }

        long accountNumber;
        string holderName, accountType;
        double initialBalance;

        cout << "\n--- Create New Account ---\n";
        cout << "Enter Account Number: ";
        cin >> accountNumber;

        if (findAccountIndex(accountNumber) != -1) {
            cout << "Account number already exists! Please try again." << endl;
            return;
        }

        cout << "Enter Account Holder Name: ";
        cin.ignore();
        getline(cin, holderName);

        cout << "Select Account Type (Savings, Business, Educational): ";
        getline(cin, accountType);

        cout << "Enter Initial Balance: ";
        cin >> initialBalance;

        if (accountType == "Savings") {
            accounts[accountCount++] = new SavingsAccount(accountNumber, holderName, initialBalance);
        } else if (accountType == "Business") {
            accounts[accountCount++] = new BusinessAccount(accountNumber, holderName, initialBalance);
        } else if (accountType == "Educational") {
            accounts[accountCount++] = new EducationalAccount(accountNumber, holderName, initialBalance);
        } else {
            cout << "Invalid account type!" << endl;
            return;
        }

        cout << "\nAccount created successfully!" << endl;
    }

    void deposit() {
        long accountNumber;
        double amount;

        cout << "\n--- Deposit Money ---\n";
        cout << "Enter Amount to Deposit: ";
        cin >> amount;
        cout << "Enter Account Number: ";
        cin >> accountNumber;

        int index = findAccountIndex(accountNumber);
        if (index == -1) {
            cout << "Invalid Account Number!" << endl;
            return;
        }

        accounts[index]->deposit(amount);
    }

    void withdraw() {
        long accountNumber;
        double amount;

        cout << "\n--- Withdraw Money ---\n";
        cout << "Enter Amount to Withdraw: ";
        cin >> amount;
        cout << "Enter Account Number: ";
        cin >> accountNumber;

        int index = findAccountIndex(accountNumber);
        if (index == -1) {
            cout << "Invalid Account Number!" << endl;
            return;
        }

        accounts[index]->withdraw(amount);
    }

    void checkBalance() {
        long accountNumber;

        cout << "\n--- Check Balance ---\n";
        cout << "Enter Account Number: ";
        cin >> accountNumber;

        int index = findAccountIndex(accountNumber);
        if (index == -1) {
            cout << "Invalid Account Number!" << endl;
            return;
        }

        accounts[index]->displayDetails();
    }

    void searchAccount() {
        cout << "\n--- Search Account ---\n";
        cout << "1. Search by Account Number\n";
        cout << "2. Search by Account Holder Name\n";
        cout << "Enter your choice: ";

        int choice;
        cin >> choice;

        if (choice == 1) {
            long accountNumber;
            cout << "Enter Account Number: ";
            cin >> accountNumber;

            int index = findAccountIndex(accountNumber);
            if (index != -1) {
                accounts[index]->displayDetails();
            } else {
                cout << "No account found with the given account number!" << endl;
            }
        } else if (choice == 2) {
            string holderName;
            cout << "Enter Account Holder Name: ";
            cin.ignore();
            getline(cin, holderName);

            bool found = false;
            for (int i = 0; i < accountCount; ++i) {
                if (accounts[i]->getHolderName() == holderName) {
                    accounts[i]->displayDetails();
                    found = true;
                }
            }

            if (!found) {
                cout << "No account found for the given holder name!" << endl;
            }
        } else {
            cout << "Invalid choice! Please try again." << endl;
        }
    }
};

// Input validation function for integer values
int getValidatedChoice() {
    int choice;
    while (true) {
        cin >> choice;
        if (cin.fail()) {
            cin.clear(); // Clear error flag
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
            cout << "Invalid input! Please enter a valid number: ";
        } else {
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear remaining input
            return choice;
        }
    }
}



int main() {

    string entryCode;

    cout << "...... Welcome to Your Banking....." << endl;

// Loop until the correct entry code is entered
do {
    cout << "\nEnter the program entry code(*889#): ";
    cin >> entryCode;

    if (entryCode != "*889#") {
        cout << "Invalid entry code. Please try again.\n";
    }
} while (entryCode != "*889#");
    Bank bank;

    while (true) {
        cout << "\n--- Bank Management System ---\n";
        cout << "\n1. Create Account\n";
        cout << "2. Deposit Money\n";
        cout << "3. Withdraw Money\n";
        cout << "4. Check Balance\n";
        cout << "5. Search Account\n";
        cout << "6. Exit\n";
        cout << "Enter your choice: ";

        int choice = getValidatedChoice();

        switch (choice) {
            case 1:
                bank.createAccount();
                break;
            case 2:
                bank.deposit();
                break;
            case 3:
                bank.withdraw();
                break;
            case 4:
                bank.checkBalance();
                break;
            case 5:
                bank.searchAccount();
                break;
            case 6:
                cout << "Exiting the program. Goodbye!" << endl;
                return 0;
            default:
                cout << "Invalid choice! Please try again." << endl;
        }
        // Ask if the user wants to exit or go back
        char nextAction;
        cout << "\n Do you want to go back to main menu press # \n or Exit * \n";
        cin >> nextAction;
        if (nextAction == '*') {
            cout << "Exiting the program. Goodbye!" << endl;
            break;
        }
    }

    return 0;
}


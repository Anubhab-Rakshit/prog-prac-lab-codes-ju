#include <iostream>
#include <string>
#include <map>
#include <iomanip>

// Forward declaration is necessary because Account and Withdraw reference each other.
class Account;
class AccountList;
class Withdraw; 

// --------------------------------------------------
// 1. Account Class (Declares friend)
// --------------------------------------------------
class Account {
private:
    std::string accountNumber;
    double balance;

    // Grant the Withdraw class full access to private members
    friend class Withdraw; 

public:
    // Constructor
    Account(const std::string& accNum, double initialBalance)
        : accountNumber(accNum), balance(initialBalance) {}

    // --- Accessors (Getters) ---
    std::string getAccountNumber() const { return accountNumber; }
    double getBalance() const { return balance; }

    // Display function
    void displayInfo() const {
        std::cout << "  Account: " << accountNumber
                  << ", Balance: $" << std::fixed << std::setprecision(2) << balance
                  << std::endl;
    }
};

// --------------------------------------------------
// 2. AccountList Class (Same as before)
// --------------------------------------------------
class AccountList {
private:
    std::map<std::string, Account> accounts;

public:
    // Add account (Uniqueness check)
    bool addAccount(const std::string& accNum, double initialBalance) {
        if (accounts.count(accNum)) {
            std::cout << "[ERROR] Account " << accNum << " already exists. Addition failed." << std::endl;
            return false;
        }
        accounts.emplace(accNum, Account(accNum, initialBalance));
        std::cout << "[SUCCESS] Account " << accNum << " added with initial balance $" << initialBalance << std::endl;
        return true;
    }

    // Find account (view)
    void findAccount(const std::string& accNum) const {
        if (accounts.count(accNum)) {
            std::cout << "\n--- Account Found ---" << std::endl;
            accounts.at(accNum).displayInfo();
            std::cout << "---------------------" << std::endl;
        } else {
            std::cout << "[ERROR] Account " << accNum << " not found." << std::endl;
        }
    }

    // Display information of all accounts
    void displayAllAccounts() const {
        std::cout << "\n--- All Accounts in List (" << accounts.size() << ") ---\n";
        if (accounts.empty()) {
            std::cout << "List is empty." << std::endl;
            return;
        }
        for (const auto& pair : accounts) {
            pair.second.displayInfo();
        }
        std::cout << "------------------------------------------" << std::endl;
    }

    // Get a modifiable reference to an account
    Account* getAccountReference(const std::string& accNum) {
        if (accounts.count(accNum)) {
            return &accounts.at(accNum);
        }
        return nullptr; 
    }
};

// --------------------------------------------------
// 3. Withdraw Class (Uses friend access)
// --------------------------------------------------
class Withdraw {
private:
    std::string accountNumber;
    double amount;

public:
    // Constructor handles the transaction logic
    Withdraw(const std::string& accNum, double amt, AccountList& list)
        : accountNumber(accNum), amount(amt) {

        // 1. Account existence check
        Account* targetAccount = list.getAccountReference(accNum);

        if (targetAccount == nullptr) {
            std::cout << "\n[WITHDRAW FAILED] Account " << accNum << " does not exist." << std::endl;
            return;
        }

        // 2. Balance check and direct update (Uses friend access to Account::balance)
        if (targetAccount->balance >= amount) { // Direct access to private member!
            targetAccount->balance -= amount;   // Direct modification to private member!
            std::cout << "\n[WITHDRAW SUCCESS] $" << amount << " withdrawn from account " << accNum << "." << std::endl;
        } else {
            std::cout << "\n[WITHDRAW FAILED] Insufficient balance on account " << accNum << "." << std::endl;
            std::cout << "  Current Balance: $" << targetAccount->balance << ", Requested: $" << amount << std::endl;
        }
    }
};

// The main function for demonstration is the same as in Implementation 1.
int main() {
    AccountList bank;

    std::cout << "--- 1. Account Addition ---\n";
    bank.addAccount("A001", 1000.00);
    bank.addAccount("B002", 500.50);

    bank.displayAllAccounts();

    std::cout << "\n--- 2. Successful Withdrawal ---\n";
    // Successful: $100 from A001 (1000 -> 900)
    Withdraw w1("A001", 100.00, bank);
    bank.findAccount("A001");

    std::cout << "\n--- 3. Failed Withdrawal (Insufficient Balance) ---\n";
    // Fail: Insufficient Balance ($900 available, request $1000)
    Withdraw w2("A001", 1000.00, bank);

    bank.displayAllAccounts();

    return 0;
}

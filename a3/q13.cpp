#include <iostream>
#include <string>
#include <iomanip>
#include <ctime>
#include <sstream>

// Helper function to get the current date/time as a string
std::string getCurrentDateTime() {
    time_t now = time(0);
    tm* ltm = localtime(&now);

    std::stringstream ss;
    ss << std::put_time(ltm, "%Y-%m-%d %H:%M:%S");
    return ss.str();
}

// --------------------------------------------------
// 1. BALANCE Class
// Holds the persistent state of the account.
// --------------------------------------------------
class Balance {
private:
    std::string accountNumber;
    double currentBalance;
    std::string lastUpdateDate;

public:
    // Constructor
    Balance(const std::string& accNum, double initialBalance)
        : accountNumber(accNum), currentBalance(initialBalance), lastUpdateDate(getCurrentDateTime()) {}

    // --- Accessors ---
    std::string getAccountNumber() const { return accountNumber; }
    double getBalance() const { return currentBalance; }
    std::string getLastUpdateDate() const { return lastUpdateDate; }

    /**
     * @brief Attempts to deduct an amount from the balance (for withdrawals).
     * @param amount The amount to withdraw.
     * @return true if the withdrawal is successful (sufficient funds), false otherwise.
     */
    bool deduct(double amount) {
        if (amount > 0 && currentBalance >= amount) {
            currentBalance -= amount;
            lastUpdateDate = getCurrentDateTime();
            return true;
        }
        return false;
    }

    /**
     * @brief Adds an amount to the balance (for deposits).
     * @param amount The amount to deposit.
     */
    void add(double amount) {
        if (amount > 0) {
            currentBalance += amount;
            lastUpdateDate = getCurrentDateTime();
        }
    }

    // Display current account status
    void displayStatus() const {
        std::cout << "\n--- Account Status: " << accountNumber << " ---" << std::endl;
        std::cout << std::fixed << std::setprecision(2);
        std::cout << "  Balance: $" << currentBalance << std::endl;
        std::cout << "  Last Update: " << lastUpdateDate << std::endl;
        std::cout << "--------------------------------------" << std::endl;
    }
};

// --------------------------------------------------
// 2. TRANSACTION Class
// Represents an operation and updates the Balance object.
// --------------------------------------------------
class Transaction {
private:
    std::string accountNumber;
    std::string dateOfTransaction;
    double amount;
    char type; // 'W' for Withdrawal, 'D' for Deposit

public:
    /**
     * @brief Constructs a transaction and executes the necessary update on the Balance object.
     * @param accNum Account number for verification.
     * @param txnAmount The monetary amount.
     * @param txnType 'W' or 'D'.
     * @param accountReference A reference to the Balance object to be updated.
     */
    Transaction(const std::string& accNum, double txnAmount, char txnType, Balance& accountReference)
        : accountNumber(accNum), amount(txnAmount), type(std::toupper(txnType)) {

        // Set transaction date
        dateOfTransaction = getCurrentDateTime();

        // 1. Basic validation
        if (accNum != accountReference.getAccountNumber()) {
            std::cout << "[TXN ERROR] Account number mismatch. Transaction aborted." << std::endl;
            return;
        }

        bool success = false;
        
        // 2. Process based on transaction type
        if (type == 'D') {
            // Deposit: Always allowed if amount > 0
            accountReference.add(amount);
            success = true;
            std::cout << "[SUCCESS] Deposit of $" << amount << " processed." << std::endl;

        } else if (type == 'W') {
            // Withdrawal: Check availability
            
            // If it is withdrawal then check whether the amount is available or not.
            if (accountReference.deduct(amount)) {
                success = true;
                std::cout << "[SUCCESS] Withdrawal of $" << amount << " processed." << std::endl;
            } else {
                std::cout << "[FAILURE] Withdrawal of $" << amount << " failed. Insufficient funds or invalid amount." << std::endl;
            }
        } else {
            std::cout << "[TXN ERROR] Invalid transaction type ('" << type << "'). Transaction aborted." << std::endl;
        }

        // Display transaction summary
        if (success) {
            displayTransaction();
        }
    }

    // Display the details of the specific transaction
    void displayTransaction() const {
        std::cout << "\n--- Transaction Summary ---" << std::endl;
        std::cout << "  Account: " << accountNumber << std::endl;
        std::cout << "  Date: " << dateOfTransaction << std::endl;
        std::cout << "  Type: " << (type == 'D' ? "Deposit" : "Withdrawal") << std::endl;
        std::cout << "  Amount: $" << std::fixed << std::setprecision(2) << amount << std::endl;
        std::cout << "---------------------------" << std::endl;
    }
};

// --------------------------------------------------
// 3. Main Function (Example Usage)
// --------------------------------------------------
int main() {
    // 1. Create a Balance object
    Balance checkingAccount("ACC12345", 500.00);
    checkingAccount.displayStatus();

    // 2. Perform a successful Deposit
    std::cout << "\n--- Performing Deposit (D) ---\n";
    Transaction txn1("ACC12345", 150.50, 'D', checkingAccount);
    checkingAccount.displayStatus(); // Balance should be $650.50

    // 3. Perform a successful Withdrawal
    std::cout << "\n--- Performing Successful Withdrawal (W) ---\n";
    Transaction txn2("ACC12345", 50.00, 'W', checkingAccount);
    checkingAccount.displayStatus(); // Balance should be $600.50

    // 4. Perform a failed Withdrawal (Insufficient funds)
    std::cout << "\n--- Performing Failed Withdrawal (W) ---\n";
    // Attempt to withdraw $700, but only $600.50 is available.
    Transaction txn3("ACC12345", 700.00, 'W', checkingAccount);
    checkingAccount.displayStatus(); // Balance should remain $600.50

    // 5. Test another successful transaction
    std::cout << "\n--- Performing Final Deposit (D) ---\n";
    Transaction txn4("ACC12345", 1000.00, 'D', checkingAccount);
    checkingAccount.displayStatus(); // Balance should be $1600.50

    return 0;
}

/*
13. Design a BALANCE class with account number, balance and date of last update. Consider a TRANSACTION class with account number, date of transaction,
amount and transaction type (W for withdrawal and D for deposit). If it is withdrawal then check whether the amount is available or not. Transaction
object will make necessary update in the BALANCE class.

Name :- Anubhab Rakshit
Class :- BCSE-II A1
Roll no:-  002410501029
*/

#include <iostream>
#include <string>
#include <iomanip>
#include <ctime>
#include <sstream>

using namespace std;

string getCurrentDateTime() {
    time_t now = time(0);
    tm* ltm = localtime(&now);

    stringstream ss;
    ss << std::put_time(ltm, "%Y-%m-%d %H:%M:%S");
    return ss.str();
}

// BALANCE Class

class Balance {

private:
    string accountNumber;
    double currentBalance;
    string lastUpdateDate;

public:
    // Constructor
    Balance(const string& accNum, double initialBalance)
        : accountNumber(accNum), currentBalance(initialBalance), lastUpdateDate(getCurrentDateTime()) {}

    string getAccountNumber() const { return accountNumber; }
    double getBalance() const { return currentBalance; }
    string getLastUpdateDate() const { return lastUpdateDate; }


    bool deduct(double amount) { //amount deduction
        if (amount > 0 && currentBalance >= amount) {
            currentBalance -= amount;
            lastUpdateDate = getCurrentDateTime();
            return true;
        }
        return false;
    }

    void add(double amount) { //amount addition
        if (amount > 0) {
            currentBalance += amount;
            lastUpdateDate = getCurrentDateTime();
        }
    }

    // Display current account status
    void displayStatus() const {
        cout << "\n--- Account Status: " << accountNumber << " ---" << endl;
        cout << "  Balance: Rs" << currentBalance << endl;
        cout << "  Last Update: " << lastUpdateDate << endl;
        cout << "--------------------------------------" << endl;
    }
};


// TRANSACTION Class

class Transaction {
private:
    string accountNumber;
    string dateOfTransaction;
    double amount;
    char type; // 'W' for Withdrawal, 'D' for Deposit

public:
    Transaction(const string& accNum, double txnAmount, char txnType, Balance& accountReference)
        : accountNumber(accNum), amount(txnAmount), type(toupper(txnType)) {

        // Set transaction date
        dateOfTransaction = getCurrentDateTime();

        // 1. Basic validation
        if (accNum != accountReference.getAccountNumber()) {
            cout << "[TXN ERROR] Account number mismatch. Transaction aborted." << endl;
            return;
        }

        bool success = false;
        
        // 2. Process based on transaction type
        if (type == 'D') {
            // Deposit: Always allowed if amount > 0
            accountReference.add(amount);
            success = true;
            cout << "[SUCCESS] Deposit of Rs" << amount << " processed." << endl;

        } else if (type == 'W') {
            
            // If it is withdrawal then check whether the amount is available or not.
            if (accountReference.deduct(amount)) {
                success = true;
                cout << "[SUCCESS] Withdrawal of Rs" << amount << " processed." << endl;
            } else {
                cout << "[FAILURE] Withdrawal of Rs" << amount << " failed. Insufficient funds or invalid amount." << endl;
            }
        } else {
            cout << "[TXN ERROR] Invalid transaction type ('" << type << "'). Transaction aborted." << endl;
        }

        // Display transaction summary
        if (success) {
            displayTransaction();
        }
    }

    // Display the details of the specific transaction
    void displayTransaction() const {
        cout << "\n--- Transaction Summary ---" << endl;
        cout << "  Account: " << accountNumber << endl;
        cout << "  Date: " << dateOfTransaction << endl;
        cout << "  Type: " << (type == 'D' ? "Deposit" : "Withdrawal") << endl;
        cout << "  Amount: Rs." << amount << endl;
        cout << "---------------------------" << endl;
    }
};


int main() {

    string accnum;
    double quan;
    char type;
    cout<<"Enter your acc number and initial balance :- ";
    cin>>accnum>>quan;
    Balance checkingAccount(accnum,quan);
    int f=1;
    while(f){
        cout<<"MENU :- \n1. Deposit \n2. Withdrawal \n3. Check Account info \n4. Exit "<<endl;
        int ch;
        cin>>ch;
        if(ch==1){
                cout<<"Enter the amount you want to deposit :- ";
                cin>>quan;
                Transaction txn(accnum,quan,'D',checkingAccount);
        }
        if(ch==2){
                cout<<"Enter the amount you want to withdraw :- ";
                cin>>quan;
                Transaction txn(accnum,quan,'W',checkingAccount);
        }
        if(ch==3){
     
                checkingAccount.displayStatus();
    
        }
        if(ch==4){
                f=0;
    
        }
    }

    return 0;
}
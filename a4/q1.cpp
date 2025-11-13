/*
1. Design the class(es) for the following. Each account has account number and balance amount. A list of account is to be maintained where one can add and
find account, display information of all accounts. While adding, account number must be unique. Withdraw object has account number (must exist) and amount
(will not exceed balance amount of corresponding account). Withdraw object will update the balance of corresponding account in the list. User will be able to
search and view account, add account and withdraw money from the account. Implement your design. Use friend function wherever required and
again, modify your implementation to avoid friend function.

Name:- Anubhab Rakshit
Class:- BCSE-II A1
Roll No:- 002410501029

*/

#include <iostream>
#include <string>
#include <map>
#include <iomanip>


class Account;
class AccountList;
class Withdraw; 

using namespace std;

class Account {
    string accountNumber;
    double balance;
    friend class Withdraw;  // Grant the Withdraw class full access to private members

public:
    Account(const string& accNum, double initialBalance)
        : accountNumber(accNum), balance(initialBalance) {}


    string getAccountNumber() const { return accountNumber; }

    double getBalance() const { return balance; }

    // Display function
    void displayInfo() const {
        cout << "  Account: " << accountNumber << ", Balance: Rs" << balance << endl;
    }
};


class AccountList {
private:
    map<string, Account> accounts;

public:
    
    bool addAccount(const string& accNum, double initialBalance) {   // Add account (Uniqueness check)

        if (accounts.count(accNum)) {
            cout << "Account " << accNum << " already exists. Addition failed." << endl;
            return false;
        }
        accounts.emplace(accNum, Account(accNum, initialBalance));
        cout << "Account " << accNum << " added with initial balance Rs." << initialBalance << endl;
        return true;
    }

    // Find account 
    void findAccount(const string& accNum) const {
        if (accounts.count(accNum)) {
            cout << "\n--- Account Found ---" << endl;
            accounts.at(accNum).displayInfo();
        } else {
            std::cout << "[ERROR] Account " << accNum << " not found." <<  endl;
        }
    }

    // Display information of all accounts
    void displayAllAccounts() const {
        cout << "\nAll Accounts in List (" << accounts.size() << ") \n";
        if (accounts.empty()) {
            cout << "List is empty." << endl;
            return;
        }
        for (auto& pair : accounts) {
            pair.second.displayInfo();
        }
    }

    // Get a modifiable reference to an account
    Account* getAccountReference(const string& accNum) {
        if (accounts.count(accNum)) {
            return &accounts.at(accNum);
        }
        return nullptr; 
    }
};


class Withdraw {
private:
    string accountNumber;
    double amount;

public:

    Withdraw(const string& accNum, double amt, AccountList& list)
        : accountNumber(accNum), amount(amt) {

        // 1. Account existence check
        Account* targetAccount = list.getAccountReference(accNum);

        if (targetAccount == nullptr) {
            cout << "\nAccount " << accNum << " does not exist." << endl;
            return;
        }

        
        if (targetAccount->balance >= amount) { 
            targetAccount->balance -= amount;  
            cout << "\nRs. " << amount << " withdrawn from account " << accNum << "." << endl;
        } else {
            cout << "\nInsufficient balance on account " << accNum << "." << endl;
            cout << "  Current Balance: Rs." << targetAccount->balance << ", Requested: Rs." << amount << endl;
        }
    }
};


int main() {
    AccountList bank;
    int f=1;
    string Accnum;
    double rate;

    while(f){
        cout<<"MENU :- \n1. Add Account \n2. Display Accounts \n3. Account info selective \n4. Withdraw from Account \n5. Exit"<<endl;
        int ch;
        cout<<"Enter your choice :- \n";
        cin>>ch;
        if(ch==1){
            cout<<"Enter acc number and initial balance :- ";
            cin>>Accnum>>rate;
            bank.addAccount(Accnum,rate);
        }
        if(ch==2){
            cout<<"Display All Accounts info :-" <<endl;
            bank.displayAllAccounts();
        }
        if(ch==3){
            cout<<"Enter Account Number whose info you want :- ";
            cin>>Accnum;
            bank.findAccount(Accnum);
        }
        if(ch==4){
            cout<<"Enter Account Number and amount you want to withdraw";
            cin>>Accnum>>rate;
            Withdraw w(Accnum,rate,bank);
        }
        if(ch==5){
            f=0;
        }
    }
    return 0;
}
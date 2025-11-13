/*
12. Design the class(es) for the following scenario :
    * An item list contains item code , name , rate and quantity for several items.
    * Whenever a new item is added in the list uniqueness of item code is to be checked.
    * Time to time rate of the items may change.
    * Whenever an item is issues or received existence of th item is checked and quantity is updated.
    * In case of issue, availability of quantity is also to be checked.
    * User may also like to know price/quantity available for an item.
    
Name :- Anubhab Rakshit
Class :- BCSE-II A1
Roll no:-  002410501029
*/


#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <iomanip>

using namespace std; 

class Item {
private:
    string code;
    string name;
    double rate;
    int quantity;

public:
    Item(const string& c, const string& n, double r, int q)
        : code(c), name(n), rate(r), quantity(q) {}

    std::string getCode() const { 
        return code;
    }
    std::string getName() const { 
        return name;
    }
    double getRate() const { 
        return rate; 
    }
    int getQuantity() const { 
        return quantity; 
    }

    void updateRate(double newRate) {
        if (newRate >= 0) {
            rate = newRate;
            cout << "Rate updated for item " << code << " to Rs." << rate << endl;
        } else {
            cout << "Error: New rate cannot be negative." << endl;
        }
    }
    bool receive(int amount) {
        if (amount > 0) {
            quantity += amount;
            return true;
        }
        cout << "Error: Receive amount must be positive." << endl;
        return false;
    }

    bool issue(int amount) {
        if (amount <= 0) {
            cout << "Error: Issue amount must be positive." << endl;
            return false;
        }
        if (quantity >= amount) {
            quantity -= amount;
            return true;
        } else {
            cout << "Issue failed for item " << code << ": Insufficient quantity. Available: " << quantity << ", Requested: " << amount << "." << endl;
            return false;
        }
    }

  
    void display() const {
       cout << "  Code: " << code << ", Name: " << name << ", Rate: Rs." << rate << ", Qty: " << quantity  << endl;
    }
};


class ItemList {
private:
    map<string, Item> items;

public:
    bool addItem(const string& code, const string& name, double rate, int quantity) {
        if (items.count(code)) {
            cout << "Error: Item with code '" << code << "' already exists. Addition failed." << endl;
            return false;
        }

        items.emplace(code, Item(code, name, rate, quantity));
        cout << "New item '" << name << "' added successfully." << endl;
        return true;
    }

    bool setRate(const string& code, double newRate) {
        if (items.count(code)) {
            items.at(code).updateRate(newRate);
            return true;
        }
        cout << "Error: Item with code '" << code << "' not found. Rate update failed." << endl;
        return false;
    }

    // Whenever an item is issued or received existence of the item is checked and quantity is updated.
    // In case of issue, availability of quantity is also to be checked.
    bool issueItem(const string& code, int amount) {
        if (!items.count(code)) {
            cout << "Error: Item with code '" << code << "' not found. Issue failed." << endl;
            return false;
        }
        // Quantity check handled inside Item::issue
        bool success = items.at(code).issue(amount);
        if (success) {
            cout << "Issued " << amount << " units of item " << code << "." << endl;
        }
        return success;
    }

    // Whenever an item is issued or received existence of the item is checked and quantity is updated.
    bool receiveItem(const string& code, int amount) {

        if (!items.count(code)) {
            cout << "Error: Item with code '" << code << "' not found. Receive failed." << endl;
            return false;
        }
        bool success = items.at(code).receive(amount);
        if (success) {
            cout << "Received " << amount << " units of item " << code << "." << endl;
        }
        return success;
    }

    //to know price/quantity available for an item.
    void queryItem(const string& code) const {
        if (items.count(code)) {
            const Item& item = items.at(code);
            cout << "\n--- Item Query: " << item.getName() << " (" << code << ") ---" << endl;
            cout << "  Current Rate: Rs" << item.getRate() << endl;
            cout << "  Quantity Available: " << item.getQuantity() << endl;
        } else {
            cout << "Query failed: Item with code '" << code << "' not found." << endl;
        }
    }

    void displayAllItems() const {
        cout << "\n--- Full Inventory List (" << items.size() << " items) ---" << endl;
        for (const auto& pair : items) {
            pair.second.display();
        }
       cout << "------------------------------------------" << endl;
    }
};


int main() {
    ItemList inventory;
    string item,code;
    float rate;
    int quan;
    int f=1;
    while(f){
        cout<<" MENU:-  \n 1. Add items \n 2. Change rate \n 3. Check items info \n 4. Issue item \n 5. Receive item \n 6. Exit " <<endl;
        int ch;
        cout<<"Enter your choice :- ";
        cin>>ch;
        switch(ch){
            case 1:
                cout<<"Enter Item code and Item name :-";
                cin>>item>>code;
                cout<<"Enter price and quantity :- ";
                cin>>rate>>quan;
                inventory.addItem(code,item,rate,quan);
                break;
            case 2:
                cout<<"Enter Item name to change :-";
                cin>>code;
                cout<<"Enter your new rate :- ";
                cin>>rate;
                inventory.setRate(code,rate);
                break;
            case 3:
                cout<<"Enter item name to check info :- ";
                cin>>item;
                inventory.queryItem(item);
                break;
            case 4:
                cout<<"Enter item name and quantity to issue :- ";
                cin>>code>>quan;
                inventory.issueItem(code,quan);
                break;
            case 5:
                cout<<"Enter item name and quantity to receive :- ";
                cin>>code>>quan;
                inventory.receiveItem(code,quan);
                break;
            case 6:
                f=0;
                break;
            default: cout<<"Invalid choice \n";
        }
    }
    return 0;
}
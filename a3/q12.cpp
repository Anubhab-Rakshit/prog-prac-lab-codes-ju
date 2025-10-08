#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <iomanip> // For setprecision

// --------------------------------------------------
// 1. Item Class: Represents a single inventory item.
// --------------------------------------------------
class Item {
private:
    std::string code;
    std::string name;
    double rate;
    int quantity;

public:
    // Constructor
    Item(const std::string& c, const std::string& n, double r, int q)
        : code(c), name(n), rate(r), quantity(q) {}

    // --- Accessors (Getters) ---
    std::string getCode() const { return code; }
    std::string getName() const { return name; }
    double getRate() const { return rate; }
    int getQuantity() const { return quantity; }

    // --- Mutators (Setters for updates) ---

    // Time to time rate of the items may change.
    void updateRate(double newRate) {
        if (newRate >= 0) {
            rate = newRate;
            std::cout << "Rate updated for item " << code << " to $" << std::fixed << std::setprecision(2) << rate << std::endl;
        } else {
            std::cout << "Error: New rate cannot be negative." << std::endl;
        }
    }

    // Whenever an item is received existence of the item is checked (handled by ItemList)
    // and quantity is updated.
    bool receive(int amount) {
        if (amount > 0) {
            quantity += amount;
            return true;
        }
        std::cout << "Error: Receive amount must be positive." << std::endl;
        return false;
    }

    // Whenever an item is issued existence of the item is checked (handled by ItemList)
    // and quantity is updated.
    // In case of issue, availability of quantity is also to be checked.
    bool issue(int amount) {
        if (amount <= 0) {
            std::cout << "Error: Issue amount must be positive." << std::endl;
            return false;
        }
        if (quantity >= amount) {
            quantity -= amount;
            return true;
        } else {
            std::cout << "Issue failed for item " << code << ": Insufficient quantity. Available: " << quantity << ", Requested: " << amount << "." << std::endl;
            return false;
        }
    }

    // Displays item information
    void display() const {
        std::cout << "  Code: " << code
                  << ", Name: " << name
                  << ", Rate: $" << std::fixed << std::setprecision(2) << rate
                  << ", Qty: " << quantity
                  << std::endl;
    }
};

// --------------------------------------------------
// 2. ItemList Class: Manages the collection of Items.
// --------------------------------------------------
class ItemList {
private:
    // Using std::map<ItemCode, Item> for fast lookup and inherent code uniqueness
    std::map<std::string, Item> items;

public:
    // Whenever a new item is added in the list uniqueness of item code is to be checked.
    bool addItem(const std::string& code, const std::string& name, double rate, int quantity) {
        // Check for uniqueness of item code
        if (items.count(code)) {
            std::cout << "Error: Item with code '" << code << "' already exists. Addition failed." << std::endl;
            return false;
        }

        // Add the new item
        items.emplace(code, Item(code, name, rate, quantity));
        std::cout << "New item '" << name << "' added successfully." << std::endl;
        return true;
    }

    // Time to time rate of the items may change.
    bool setRate(const std::string& code, double newRate) {
        // Check existence
        if (items.count(code)) {
            items.at(code).updateRate(newRate);
            return true;
        }
        std::cout << "Error: Item with code '" << code << "' not found. Rate update failed." << std::endl;
        return false;
    }

    // Whenever an item is issued or received existence of the item is checked and quantity is updated.
    // In case of issue, availability of quantity is also to be checked.
    bool issueItem(const std::string& code, int amount) {
        // Check existence
        if (!items.count(code)) {
            std::cout << "Error: Item with code '" << code << "' not found. Issue failed." << std::endl;
            return false;
        }
        // Quantity check handled inside Item::issue
        bool success = items.at(code).issue(amount);
        if (success) {
            std::cout << "Issued " << amount << " units of item " << code << "." << std::endl;
        }
        return success;
    }

    // Whenever an item is issued or received existence of the item is checked and quantity is updated.
    bool receiveItem(const std::string& code, int amount) {
        // Check existence
        if (!items.count(code)) {
            std::cout << "Error: Item with code '" << code << "' not found. Receive failed." << std::endl;
            return false;
        }
        bool success = items.at(code).receive(amount);
        if (success) {
            std::cout << "Received " << amount << " units of item " << code << "." << std::endl;
        }
        return success;
    }

    // User may also like to know price/quantity available for an item.
    void queryItem(const std::string& code) const {
        if (items.count(code)) {
            const Item& item = items.at(code);
            std::cout << "\n--- Item Query: " << item.getName() << " (" << code << ") ---" << std::endl;
            std::cout << "  Current Rate: $" << std::fixed << std::setprecision(2) << item.getRate() << std::endl;
            std::cout << "  Quantity Available: " << item.getQuantity() << std::endl;
        } else {
            std::cout << "Query failed: Item with code '" << code << "' not found." << std::endl;
        }
    }

    void displayAllItems() const {
        std::cout << "\n--- Full Inventory List (" << items.size() << " items) ---" << std::endl;
        for (const auto& pair : items) {
            pair.second.display();
        }
        std::cout << "------------------------------------------" << std::endl;
    }
};

// --------------------------------------------------
// 3. Example Usage
// --------------------------------------------------
int main() {
    ItemList inventory;

    std::cout << "--- 1. Initial Item Addition ---\n";
    // Add new items (Uniqueness check is handled)
    inventory.addItem("A101", "Laptop", 1200.00, 50);
    inventory.addItem("B202", "Monitor", 350.50, 100);
    inventory.addItem("A101", "Duplicate Laptop", 1000.00, 10); // Check uniqueness (will fail)

    inventory.displayAllItems();

    std::cout << "\n--- 2. Rate Change ---\n";
    // Change rate (Existence checked)
    inventory.setRate("A101", 1150.99);
    inventory.setRate("Z999", 50.00); // Check existence (will fail)

    inventory.queryItem("A101");

    std::cout << "\n--- 3. Issuing and Receiving ---\n";
    // Issue item (Existence and availability checked)
    inventory.issueItem("B202", 15);
    inventory.issueItem("B202", 100); // Check availability (will fail: 100 - 15 = 85 available)

    // Receive item (Existence checked)
    inventory.receiveItem("A101", 10);
    inventory.receiveItem("Z999", 5); // Check existence (will fail)

    inventory.queryItem("B202");
    inventory.queryItem("A101");

    return 0;
}

/* 3. Employee has unique emp-id, name, designation and basic pay. An employee is
either a permanent one or contractual. For permanent employee salary is
computed as basic pay+ hra (30% of basic pay) + da (80% of basic pay). For
contractual employee it is basic pay + allowance (it is different for different
contractual employee). An employee pointer may point to either of the two
categories and accordingly the salary has to be created.
Design the classes and implement.
    */


#include <iostream>
#include <string>
#include <vector>
using namespace std;

// =====================================================
// Base Class : Employee
// =====================================================
class Employee {
protected:
    int empId;
    string name;
    string designation;
    float basicPay;

public:
    Employee() {}

    virtual void input() {
        cout << "Enter Employee ID: ";
        cin >> empId;
        cin.ignore();
        cout << "Enter Name: ";
        getline(cin, name);
        cout << "Enter Designation: ";
        getline(cin, designation);
        cout << "Enter Basic Pay: ";
        cin >> basicPay;
    }

    // Virtual function to compute salary
    virtual float calculateSalary() = 0;

    virtual void showDetails() {
        cout << "\nEmployee ID: " << empId;
        cout << "\nName: " << name;
        cout << "\nDesignation: " << designation;
        cout << "\nBasic Pay: " << basicPay << endl;
    }

    virtual string getType() = 0;

    virtual ~Employee() {}
};

// =====================================================
// Derived Class : Permanent Employee
// =====================================================
class PermanentEmployee : public Employee {
public:
    float calculateSalary() override {
        float hra = 0.30f * basicPay;
        float da  = 0.80f * basicPay;
        return basicPay + hra + da;
    }

    string getType() override { return "Permanent Employee"; }

    void showDetails() override {
        cout << "\n--- Permanent Employee ---\n";
        Employee::showDetails();
        cout << "Total Salary: " << calculateSalary() << endl;
    }
};

// =====================================================
// Derived Class : Contractual Employee
// =====================================================
class ContractualEmployee : public Employee {
    float allowance;

public:
    void input() override {
        Employee::input();
        cout << "Enter Allowance: ";
        cin >> allowance;
    }

    float calculateSalary() override {
        return basicPay + allowance;
    }

    string getType() override { return "Contractual Employee"; }

    void showDetails() override {
        cout << "\n--- Contractual Employee ---\n";
        Employee::showDetails();
        cout << "Allowance: " << allowance;
        cout << "\nTotal Salary: " << calculateSalary() << endl;
    }
};

// =====================================================
// MAIN (Menu-Driven)
// =====================================================
int main() {
    vector<Employee*> empList;
    int choice;

    while (true) {
        cout << "\n===== EMPLOYEE MANAGEMENT SYSTEM =====\n";
        cout << "1. Add Permanent Employee\n";
        cout << "2. Add Contractual Employee\n";
        cout << "3. Show All Employees\n";
        cout << "4. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        if (choice == 1) {
            Employee* e = new PermanentEmployee();
            e->input();
            empList.push_back(e);
            cout << "\nPermanent Employee Added.\n";
        }
        else if (choice == 2) {
            Employee* e = new ContractualEmployee();
            e->input();
            empList.push_back(e);
            cout << "\nContractual Employee Added.\n";
        }
        else if (choice == 3) {
            cout << "\n----- EMPLOYEE DETAILS -----\n";
            for (size_t i = 0; i < empList.size(); i++) {
                cout << "\nEmployee Index: " << i;
                cout << "\nType: " << empList[i]->getType();
                empList[i]->showDetails();
                cout << "\n---------------------------\n";
            }
        }
        else if (choice == 4) {
            cout << "\nExiting...\n";
            break;
        }
        else {
            cout << "\nInvalid choice! Try again.\n";
        }
    }

    // Free memory
    for (Employee* e : empList)
        delete e;

    return 0;
}

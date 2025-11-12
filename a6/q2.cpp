/*

    2. Consider a class Student with roll, name and score as attributes. Support to take and
display data is also there. One wants to works with array of Student objects. May
collect data for array elements, display those. In case index goes out of bounds,
exception is to be raised with suitable message.
    */


#include <iostream>
#include <string>
using namespace std;

// ===============================================
// Student Class
// ===============================================
class Student {
    int roll;
    string name;
    float score;

public:
    Student() : roll(0), score(0) {}

    void input() {
        cout << "Enter Roll: ";
        cin >> roll;
        cin.ignore();
        cout << "Enter Name: ";
        getline(cin, name);
        cout << "Enter Score: ";
        cin >> score;
    }

    void display() const {
        cout << "\nRoll: " << roll
             << "\nName: " << name
             << "\nScore: " << score << endl;
    }
};

// ===============================================
// MAIN
// ===============================================
int main() {
    int n;
    cout << "Enter number of students: ";
    cin >> n;

    Student *arr = new Student[n];

    cout << "\n--- Enter Student Details ---\n";
    for (int i = 0; i < n; i++) {
        cout << "\nStudent " << i << ":\n";
        arr[i].input();
    }

    cout << "\nEnter index to display: ";
    int idx;
    cin >> idx;

    // ==============================
    // Exception Handling with try/catch
    // ==============================
    try {
        if (idx < 0 || idx >= n) {
            throw "Index out of bounds!";   // Exception triggered
        }

        // Valid index
        cout << "\n--- Student Details ---\n";
        arr[idx].display();
    }
    catch (const char *msg) {
        cout << "\nException Caught: " << msg << endl;
    }

    delete[] arr;
    return 0;
}

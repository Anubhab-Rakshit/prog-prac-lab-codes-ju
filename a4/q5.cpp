/*

Modify the STRING class so that assigning/initializing a string by another will
not copy it physically but will keep a reference count, which will be incremented.
Reference value 0 means the space can be released 

Name :- Anubhab Rakshit
Class :- BCSE-II A1
Roll Number:- 002410501029

*/


#include <iostream>
#include <cstring>
using namespace std;

class STRING {
private:
    char *str;      // Pointer to actual string data
    int *refCount;  // Reference count pointer

public:
    // Default constructor
    STRING() {
        str = new char[1];
        str[0] = '\0';
        refCount = new int(1);
    }

    // Parameterized constructor
    STRING(const char *s) {
        str = new char[strlen(s) + 1];
        strcpy(str, s);

        refCount = new int(1);  // First owner of string
    }

    // Copy constructor (reference incrementing)
    STRING(const STRING &obj) {
        str = obj.str;
        refCount = obj.refCount;
        (*refCount)++;  // Increase reference count
    }

    // Assignment operator (reference counting)
    STRING& operator=(const STRING &obj) {
        if (this != &obj) {  // Avoid self assignment
            (*refCount)--;   

            // If no one is referencing, delete memory
            if (*refCount == 0) {
                delete[] str;
                delete refCount;
            }

            // Share the new reference
            str = obj.str;
            refCount = obj.refCount;
            (*refCount)++;
        }
        return *this;
    }

    // Display function
    void display() const {
        cout << str << " (refCount=" << *refCount << ")" << endl;
    }

    // Destructor (reference decrementing)
    ~STRING() {
        (*refCount)--;

        if (*refCount == 0) {
            delete[] str;
            delete refCount;
        }
    }
};

int main() {
    STRING s1("Hello I am Anubhab");

    cout << "s1: ";
    s1.display();

    STRING s2 = s1;  // Copy constructor (no copying memory)
    cout << "s2 (after copy): ";
    s2.display();

    STRING s3;
    s3 = s1; // Assignment (no copying memory)
    cout << "s3 (after assignment): ";
    s3.display();

    return 0;
}
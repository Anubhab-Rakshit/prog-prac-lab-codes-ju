/*
4. Design a STRING class, which will have the initialization facility similar to array
class. Provide support for
• Assigning one object for another,
• Two string can be concatenated using + operator,
• Two strings can be compared using the relational operators.

*/


#include <iostream>
#include <cstring>
using namespace std;

class STRING {
private:
    char *str;
    int length;

public:
    // ✅ Default constructor
    STRING() {
        length = 0;
        str = new char[1];
        str[0] = '\0';
    }

    // ✅ Parameterized constructor (initialization facility)
    STRING(const char *s) {
        length = strlen(s);
        str = new char[length + 1];
        strcpy(str, s);
    }

    void input_str(){
        char buffer[100];
        cin >> buffer;
        length = strlen(buffer);
        delete[] str; // Free existing memory
        str = new char[length + 1];
        strcpy(str, buffer);
    }
    void display_str(){
        cout << str << endl;
    }

    // ✅ Copy constructor
    STRING(const STRING &obj) {
        length = obj.length;
        str = new char[length + 1];
        strcpy(str, obj.str);
    }

    // ✅ Assignment operator overloading
    STRING operator=(const STRING &obj) {
        if (this != &obj) {  // Avoid self-assignment
            delete[] str;
            length = obj.length;
            str = new char[length + 1];
            strcpy(str, obj.str);
        }
        return *this;
    }

    // ✅ Concatenation operator overloading
    STRING operator+(const STRING &obj) {
        STRING temp;
        temp.length = length + obj.length;
        temp.str = new char[temp.length + 1];

        strcpy(temp.str, str);
        strcat(temp.str, obj.str);

        return temp;
    }

    // ✅ Relational operator overloads (comparison)
    bool operator==(const STRING &obj) { return strcmp(str, obj.str) == 0; }
    bool operator!=(const STRING &obj) { return strcmp(str, obj.str) != 0; }
    bool operator<(const STRING &obj) { return strcmp(str, obj.str) < 0; }
    bool operator>(const STRING &obj) { return strcmp(str, obj.str) > 0; }
    bool operator<=(const STRING &obj) { return strcmp(str, obj.str) <= 0; }
    bool operator>=(const STRING &obj) { return strcmp(str, obj.str) >= 0; }

   

    // ✅ Destructor
    ~STRING() {
        delete[] str;
    }
};

int main() {
    STRING s1, s2, s3, s4;
    int choice;
    while (1) {
        cout << "\nMENU :- \n 1. Initialize Strings \n 2. Concatenate Strings \n 3. Compare Strings \n 4. Input Strings again \n 5. Exit";
        cin >> choice;
        switch (choice) {
            case 1:
                cout << "Enter the first string: ";
                s1.input_str();
                cout << "Enter the second string: ";
                s2.input_str();
                break;
            case 2:
                s3 = s1 + s2;
                cout << "After concatenation: ";
                s3.display_str();
                break;
            case 3:
                if (s1 == s2) cout << "The strings are equal" << endl;
                if (s1 != s2) cout << "The strings are not equal" << endl;
                if (s1 < s2) cout << "The first string is smaller than the second string" << endl;
                if (s1 > s2) cout << "The first string is greater than the second string" << endl;
                
            
                break;
            case 4:
                cout << "Enter the first string: ";
                s1.input_str();
                cout << "Enter the second string: ";
                s2.input_str();
                break;
            case 5:
                exit(0);
                break;
            default:
                cout << "Invalid choice" << endl;
        }
    }
    return 0;
}


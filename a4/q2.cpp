/*
Design a COMPLEX class, which will behave like normal integer with respect to
• addition,
• subtraction,
• accepting the value and
• Displaying the value.

Name :- Anubhab Rakshit
Class :- BCSE-II A1
Roll Number:- 002410501029


*/



#include <iostream>
#include <iomanip>

using namespace std;
class COMPLEX {
private:
    double real;
    double imag; 

public:
    // Constructor
    COMPLEX(double r = 0.0, double i = 0.0) : real(r), imag(i) {}

    COMPLEX operator+(const COMPLEX& other) const {  //operator overloading +
        return COMPLEX(real + other.real, imag + other.imag);
    } 

    COMPLEX operator-(const COMPLEX& other) const {  //operator overloading -
        return COMPLEX(real - other.real, imag - other.imag);
    }

    friend istream& operator>>(istream& is, COMPLEX& c) { //operator overloading >>
     
        char ch1, ch2, ch3;
        
        cout << "Enter complex number (format: real imag): ";
        is >> c.real >> c.imag;
        return is;
    }
    
 
    friend ostream& operator<<(ostream& os, const COMPLEX& c) { // //operator overloading <<
        os << c.real;
        
        if (c.imag >= 0) {
            os << " + " << c.imag << "i";
        } else {
            os << " - " << (-c.imag) << "i";
        }
        return os;
    }

    void display() const { //display func
        cout << *this << endl;
    }
};

//menu

int main() {
    COMPLEX c1, c2, c_sum, c_diff;
    int ch;
    int f=1;
    while(f)
    {
        cout<<"\nMENU :- \n1. Addition\n2. Subtraction\n3. Display\n4. Accept\n5. Exit\nEnter your choice: ";
        cin>>ch;
        if(ch==1){
            c_sum = c1 + c2;
            cout << "Sum: " << c_sum << endl;
        }
        else if(ch==2){
            c_diff = c1 - c2;
            cout << "Difference: " << c_diff << endl;
        }
        else if(ch==3){
            cout << "C1 is: " << c1 << endl;
            cout << "C2 is: " << c2 << endl;
        }
        else if(ch==4){
            cout << "For c1: ";
            cin >> c1; 
    
            cout << "For c2: ";
            cin >> c2;
        }
        else {
            f=0;
        }
    }

    return 0;
}
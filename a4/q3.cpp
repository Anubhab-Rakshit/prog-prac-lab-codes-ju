/*
3. Design an ARRAY of integer class with the following features:
a. Array object may be declared for a specific size and a value for initializing
all the elements. Default values for the parameters may be taken as 0.
b. An array object may be declared and initialized with another object.
c. An array object may be declared and initialized with another array (not
the object, standard array as in C language).


Name :- Anubhab Rakshit
Class :- BCSE-II A1
Roll Number:- 002410501029


*/

#include <iostream>
#include <algorithm> // For copy

using namespace std;

//array class
class ARRAY {
private:
    int* data;
    int size;

public:
    ARRAY(int s = 10, int initialValue = 0) : size(s) { //initialize 
        if (size <= 0) {
            cout << "Error: Array size must be positive. Defaulting to size 10." << endl;
            this->size = 10;
        }
        data = new int[this->size];
        for (int i = 0; i < this->size; ++i) {
            data[i] = initialValue;
        }
    }

    ARRAY(const ARRAY& other) : size(other.size) { //copy constructor
        cout << "Copy constructor called.\n";
        data = new int[size];
        copy(other.data, other.data + size, data);
    }

    ARRAY(const int* standardArray, int s) : size(s) {
        if (size <= 0) {
            cout << "C-array size must be positive. Defaulting to size 1." << endl;
            this->size = 1;
            data = new int[1]{0};
            return;
        }
        data = new int[size];

        
        copy(standardArray, standardArray + size, data);
    }

    ~ARRAY() { //destructor
        delete[] data;
        data = nullptr;
    }

 
    ARRAY operator+(const ARRAY& other) const { //operator overloading
    
        if (size != other.size) {
            cout << "Array sizes mismatch for addition. Returning LHS array." <<endl;
            return *this; 
        }
        
   
        ARRAY result(size);
        for (int i = 0; i < size; ++i) {
            result.data[i] = this->data[i] + other.data[i];
        }
        return result;
    }

    ARRAY& operator=(const ARRAY& other) { //assignment operator overload

        if (this == &other) {
            return *this;
        }

        if (size != other.size) {
            delete[] data;
            size = other.size;
            data = new int[size];
        }
        copy(other.data, other.data + size, data);

        return *this;
    }

    int& operator[](int index) {
        if (index < 0 || index >= size) {
            cout << "Index " << index << " out of bounds! Returning first element." << endl;
            return data[0];
        }
        return data[index];
    }

    const int& operator[](int index) const {
        if (index < 0 || index >= size) {
            cout << "Index " << index << " out of bounds! Returning 0." << endl;
            return data[0]; 
        }
        return data[index];
    }
    
    // Helper function to display the array
    void display() const {
        std::cout << "[";
        for (int i = 0; i < size; ++i) {
            std::cout << data[i] << (i < size - 1 ? ", " : "");
        }
        std::cout << "]" << std::endl;
    }
};

int main() {

    int ch,f=1;
    ARRAY arr1,arr2;
    int size,initial;
    while(f)
    {

        cout<<"\nMENU :- \n1. Declaration and initialization \n2.Copy using copy constructor \n3. Addition using + operator \n4. Assignment using = operator\n5. Subscripting using [] operator \n6. Display \n7. Exit\nEnter your choice : ";
        cin>>ch;

        if(ch==1){
            cout<<"Enter size and initial value :-";
            cin>>size>>initial;
            ARRAY arr1(size,initial);

        }
        if(ch==2){
            ARRAY arr2=arr1;
            cout<<"Copied using copy constructor :- ";
            arr2.display();
            cout<<"Original Array :- ";
            arr1.display();
            
        }
        if(ch==3){
            cout << "\n--- i. Addition (a + b) ---\n";
            ARRAY arr_sum = arr1 + arr2;
            cout << "arr1 + arr3: "; arr_sum.display(); 

        }
        if(ch==4){
            ARRAY arr3;
            arr3=arr1;
            cout<<"Assigned using = operator :- ";
            arr3.display();
            cout<<"Original Array :- ";
            arr1.display();
            
        }
        if(ch==5){
            cout<<"Enter index to access element :- ";
            int index;
            cin>>index;
            cout<<"Element at index "<<index<<" is :- "<<arr1[index]<<endl;
            
        }
        if(ch==6){
            cout<<"Array :- ";
            arr1.display();
        }
        if(ch==7){
            f=0;
        }
        
    }

    
    return 0;
}
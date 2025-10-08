#include <iostream>
#include <algorithm> // For std::copy

class ARRAY {
private:
    int* data;
    int size;

public:
    // --- a. Constructor for specific size and initialization value (Default: size=10, value=0) ---
    ARRAY(int s = 10, int initialValue = 0) : size(s) {
        if (size <= 0) {
            std::cerr << "Error: Array size must be positive. Defaulting to size 10." << std::endl;
            this->size = 10;
        }
        data = new int[this->size];
        for (int i = 0; i < this->size; ++i) {
            data[i] = initialValue;
        }
    }

    // --- b. Copy Constructor (Initializes with another ARRAY object) ---
    ARRAY(const ARRAY& other) : size(other.size) {
        std::cout << "Copy constructor called.\n";
        data = new int[size];
        // Copy elements from the other object's data array
        std::copy(other.data, other.data + size, data);
    }

    // --- c. Constructor for initializing with a standard C-style array ---
    ARRAY(const int* standardArray, int s) : size(s) {
        if (size <= 0) {
            std::cerr << "Error: C-array size must be positive. Defaulting to size 1." << std::endl;
            this->size = 1;
            data = new int[1]{0};
            return;
        }
        data = new int[size];
        // Copy elements from the standard C array
        std::copy(standardArray, standardArray + size, data);
    }

    // --- Destructor (Crucial for releasing dynamically allocated memory) ---
    ~ARRAY() {
        delete[] data;
        data = nullptr;
    }

    // --- i. Operator Overloading for Addition (a + b) ---
    // Adds corresponding elements and returns a new ARRAY object.
    ARRAY operator+(const ARRAY& other) const {
        // Assume arrays have the same size for simplicity in addition
        if (size != other.size) {
            std::cerr << "Error: Array sizes mismatch for addition. Returning LHS array." << std::endl;
            return *this; 
        }
        
        // Create a new ARRAY object to store the result
        ARRAY result(size);
        for (int i = 0; i < size; ++i) {
            result.data[i] = this->data[i] + other.data[i];
        }
        return result;
    }

    // --- ii. Operator Overloading for Assignment (a = b) ---
    // Assigns one array object to another, handling self-assignment and deep copy.
    ARRAY& operator=(const ARRAY& other) {
        // 1. Handle self-assignment (a = a)
        if (this == &other) {
            return *this;
        }

        // 2. Release old memory if sizes are different
        if (size != other.size) {
            delete[] data;
            size = other.size;
            data = new int[size];
        }

        // 3. Deep copy elements
        std::copy(other.data, other.data + size, data);

        return *this;
    }

    // --- iii. Operator Overloading for Subscripting (a[i]) ---
    // Version for L-value (allows modification: a[i] = value)
    int& operator[](int index) {
        if (index < 0 || index >= size) {
            std::cerr << "Error: Index " << index << " out of bounds! Returning first element." << std::endl;
            // A non-standard, but safe way to handle error by returning a reference to a valid element
            return data[0];
        }
        return data[index];
    }

    // Version for R-value (allows read-only access: cout << a[i])
    const int& operator[](int index) const {
        if (index < 0 || index >= size) {
            std::cerr << "Error: Index " << index << " out of bounds! Returning 0." << std::endl;
            // Returning a const reference to avoid modification
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

// --------------------------------------------------
// Main Function (Demonstration)
// --------------------------------------------------
int main() {
    std::cout << "--- A. Declarations and Initializations ---\n";

    // a. Array object with specified size (5) and initial value (10)
    ARRAY arr1(5, 10); 
    std::cout << "arr1 (5x10): "; arr1.display();

    // a. Array object with default parameters (10x0)
    ARRAY arr_def;
    std::cout << "arr_def (Default 10x0): "; arr_def.display();

    // b. Initialized with another object (uses Copy Constructor)
    ARRAY arr2 = arr1; 
    std::cout << "arr2 (Copy of arr1): "; arr2.display();

    // c. Initialized with a standard C-style array
    int c_arr[] = {1, 2, 3, 4, 5};
    ARRAY arr3(c_arr, 5); 
    std::cout << "arr3 (from C-array): "; arr3.display();

    std::cout << "\n--- i. Addition (a + b) ---\n";
    // arr1: [10, 10, 10, 10, 10]
    // arr3: [1, 2, 3, 4, 5]
    ARRAY arr_sum = arr1 + arr3;
    std::cout << "arr1 + arr3: "; arr_sum.display(); // Expected: [11, 12, 13, 14, 15]

    std::cout << "\n--- ii. Assignment (a = b) ---\n";
    // arr2 is currently [10, 10, 10, 10, 10]
    std::cout << "arr2 before assignment: "; arr2.display();
    arr2 = arr3; // Assignment operator called (deep copy)
    std::cout << "arr2 = arr3: "; arr2.display(); // arr2 is now [1, 2, 3, 4, 5]

    std::cout << "\n--- iii. Subscripting (a[i]) ---\n";
    std::cout << "arr3[2] (read): " << arr3[2] << std::endl; // Expected: 3

    // Modify an element (L-value use)
    arr3[4] = 99;
    std::cout << "arr3 after modification: "; arr3.display(); // Expected: [1, 2, 3, 4, 99]
    
    return 0;
}

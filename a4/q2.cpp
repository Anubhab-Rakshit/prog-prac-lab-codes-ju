#include <iostream>
#include <iomanip>

// --------------------------------------------------
// COMPLEX Class Design
// --------------------------------------------------
class COMPLEX {
private:
    double real;
    double imag; // Imaginary part

public:
    // Constructor
    COMPLEX(double r = 0.0, double i = 0.0) : real(r), imag(i) {}

    // --- 1. Operator Overloading for Addition (+) ---
    // Overloads the binary '+' operator to add two COMPLEX numbers.
    COMPLEX operator+(const COMPLEX& other) const {
        return COMPLEX(real + other.real, imag + other.imag);
    }

    // --- 2. Operator Overloading for Subtraction (-) ---
    // Overloads the binary '-' operator to subtract one COMPLEX number from another.
    COMPLEX operator-(const COMPLEX& other) const {
        return COMPLEX(real - other.real, imag - other.imag);
    }

    // --- 3. Overloading Input Stream (Accepting the value) ---
    /**
     * @brief Enables reading COMPLEX numbers directly using std::cin (e.g., cin >> c1;).
     * Format expected: (real, imag)
     */
    friend std::istream& operator>>(std::istream& is, COMPLEX& c) {
        // Read expected format like: (3.5, 2.0)
        char ch1, ch2, ch3;
        
        std::cout << "Enter complex number (format: real imag): ";
        // We'll simplify input to just two doubles separated by space for basic acceptance
        if (is >> c.real >> c.imag) {
            // Optional: check for specific format like (a, b)
            // Example for (a, b) format: if (is >> ch1 >> c.real >> ch2 >> c.imag >> ch3)
        }
        return is;
    }
    
    // --- 4. Overloading Output Stream (Displaying the value) ---
    /**
     * @brief Enables writing COMPLEX numbers directly using std::cout (e.g., cout << c1;).
     * Output format: a + bi
     */
    friend std::ostream& operator<<(std::ostream& os, const COMPLEX& c) {
        os << std::fixed << std::setprecision(2) << c.real;
        
        if (c.imag >= 0) {
            os << " + " << c.imag << "i";
        } else {
            // If imaginary part is negative, use " - " and the absolute value
            os << " - " << (-c.imag) << "i";
        }
        return os;
    }

    // Helper to display data (can be used alternatively to stream operator)
    void display() const {
        std::cout << *this << std::endl;
    }
};

// --------------------------------------------------
// Main Function (Demonstration)
// --------------------------------------------------
int main() {
    COMPLEX c1, c2, c_sum, c_diff;
    
    std::cout << "--- Accepting Values (like 'cin >> int') ---" << std::endl;
    // 1. Accepting the value (using overloaded >>)
    std::cout << "For c1: ";
    std::cin >> c1; 
    
    std::cout << "For c2: ";
    std::cin >> c2; 

    // Clear the input buffer in case of errors
    if (std::cin.fail()) {
        std::cin.clear();
        std::cin.ignore(10000, '\n');
    }

    std::cout << "\n--- Displaying Values (like 'cout << int') ---" << std::endl;
    // 2. Displaying the value (using overloaded <<)
    std::cout << "C1 is: " << c1 << std::endl;
    std::cout << "C2 is: " << c2 << std::endl;

    std::cout << "\n--- Addition (like 'int + int') ---" << std::endl;
    // 3. Addition (using overloaded +)
    c_sum = c1 + c2;
    std::cout << c1 << " + " << c2 << " = " << c_sum << std::endl;

    std::cout << "\n--- Subtraction (like 'int - int') ---" << std::endl;
    // 4. Subtraction (using overloaded -)
    c_diff = c1 - c2;
    std::cout << c1 << " - " << c2 << " = " << c_diff << std::endl;

    return 0;
}

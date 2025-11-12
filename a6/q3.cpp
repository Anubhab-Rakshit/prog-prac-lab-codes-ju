#include <iostream>
#include <limits>
using namespace std;

template <class T>
class Array1D {
    T *arr;
    int size;
public:
    Array1D(int n) : size(n) { arr = new T[size]; }
    void input() {
        cout << "Enter " << size << " elements:\n";
        for (int i = 0; i < size; ++i) {
            // keep trying until a valid value is read
            while (!(cin >> arr[i])) {
                cout << "Invalid input, try again: ";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
        }
    }
    void display() const {
        cout << "\nArray Elements: ";
        for (int i = 0; i < size; ++i) cout << arr[i] << ' ';
        cout << "\n";
    }
    T sum() const {
        T s = T();                 // zero-initialized correctly for any T
        for (int i = 0; i < size; ++i) s = s + arr[i];
        return s;
    }
    T maximum() const {
        if (size <= 0) return T();
        T mx = arr[0];
        for (int i = 1; i < size; ++i)
            if (arr[i] > mx) mx = arr[i];
        return mx;
    }
    ~Array1D() { delete[] arr; }
};

int main() {
    int n;
    cout << "Enter size of array: ";
    while (!(cin >> n) || n <= 0) {
        cout << "Enter a positive integer: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    cout << "\nChoose element type:\n"
         << "1. int\n2. float\n3. double\n4. char\nEnter choice: ";
    int choice;
    cin >> choice;

    switch (choice) {
        case 1: {
            Array1D<int> A(n);
            A.input();
            A.display();
            cout << "Sum of elements: " << A.sum() << "\n";
            cout << "Maximum element: " << A.maximum() << "\n";
            break;
        }
        case 2: {
            Array1D<float> A(n);
            A.input();
            A.display();
            cout << "Sum of elements: " << A.sum() << "\n";
            cout << "Maximum element: " << A.maximum() << "\n";
            break;
        }
        case 3: {
            Array1D<double> A(n);
            A.input();
            A.display();
            cout << "Sum of elements: " << A.sum() << "\n";
            cout << "Maximum element: " << A.maximum() << "\n";
            break;
        }
        case 4: {
            Array1D<char> A(n);
            cout << "Enter " << n << " characters separated by spaces or newlines:\n";
            A.input();
            A.display();
            // For char, sum will be char-typed; cast to int to print numeric sum if you want ASCII sum
            cout << "Sum of elements (as chars): " << A.sum() << "\n";
            cout << "Maximum element: " << A.maximum() << "\n";
            break;
        }
        default:
            cout << "Invalid choice\n";
    }
    return 0;
}

#include <iostream>
using namespace std;

class Array {
private:
    int* data;
    int size;

public:
    // Parameterized constructor
    Array(int n) {
        size = n;
        data = new int[n];

        cout << "Parameterized constructor\n";
    }

    // Copy constructor
    Array(const Array& other) {
        size = other.size;
        data = new int[size];

        for (int i = 0; i < size; i++) {
            data[i] = other.data[i];
        }

        cout << "Copy constructor\n";
    }

    // Move constructor
    Array(Array&& other) {
        size = other.size;
        data = other.data;

        // Give up ownership
        other.data = nullptr;
        other.size = 0;

        cout << "Move constructor\n";
    }

    // Destructor
    ~Array() {
        delete[] data;
    }
};

int main() {

    Array a(1000);

    // Copy: creates a completely separate array
    Array b = a;

    // Move: takes the resources from a
    Array c = std::move(a);

    return 0;
}
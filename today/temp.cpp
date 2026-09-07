#include <iostream>

class Person {
public:
    int age = 25; // Real data stored inside the object

    Person() {
        std::cout << "Person() created, age = " << age << std::endl;
    }

    ~Person() {
        std::cout << "~Person() destroyed" << std::endl;
    }

    friend std::ostream& operator<<(std::ostream& os, const Person& person) {
        // We actually read the member variable from memory here!
        os << "[Person age: " << person.age << "]";
        return os;
    }
};

void demonstrate_ub() {
    Person* p = new Person();

    std::cout << "1. Before delete: " << *p << std::endl;

    delete p; // Memory is marked free, but age (25) is still sitting there
    std::cout << "2. Right after delete (ghost): " << *p << std::endl;

    // Allocate an integer array in the same memory slot that Person just occ Bupied
    int* overwrite = new int[5];
    for (int i = 0; i < 5; ++i) {
        overwrite[i] = 999999; // Spray garbage over that memory!
    }

    // Now try to read the dead person's age again:
    std::cout << "3. After memory reuse (CORRUPTED): " << *p << std::endl;

    delete[] overwrite;
}

int main() {
    demonstrate_ub();
    return 0;
}
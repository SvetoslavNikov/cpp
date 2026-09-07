#include <iostream>

int main() {
    std::cout << "Starting...\n";

    int* p = new int(42);

    std::cout << "Allocated p = " << *p << "\n";

    delete p;

    std::cout << "Deleted p\n";

    // Intentional memory bug:
    std::cout << "Trying to use p after delete...\n";
    std::cout << *p << "\n";

    return 0;
}

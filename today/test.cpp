#include <iostream>

int main() {
    std::cout << "HELLO FROM C++" << std::endl;

    int* p = new int(42);
    std::cout << "Before delete: " << *p << std::endl;

    delete p;

    std::cout << "About to trigger ASan..." << std::endl;
    std::cout << *p << std::endl;

    return 0;
}

#include <iostream>




int main() {
    int x = 10;

    int& reference = x;
    reference = 20; //x stava 20


    int* p = &x;

    *p = 30;

    std::cout << x << "\n";
    std::cout << &x << "\n";
    std::cout << reference << "\n";
    std::cout << &reference << "\n";

    std::cout << p << "\n";
    std::cout << *p << "\n";





}
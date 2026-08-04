#include <iostream>


class Box{
    int i;
public:
    Box(int i) : i(i){};

    void print() const;
};

void Box::print() const {
    std::cout << this->i;
}

int main() {
    Box b0();
    Box b1 = 1;
    b1 = Box(1);
    Box b2(1);
    Box b3 = Box(1);
}

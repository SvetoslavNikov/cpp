#include <iostream>

class Box {
    int i;
public:
    // default: Box b;  — без аргументи
    Box() : i(0){};
    // параметризиран: Box b(5);
    Box(int i) : i(i){};
    // copy: Box b2(b1);  — НОВ обект от стар (не е b2 = b1)
    Box(const Box& box) : i(box.get()){};

    // dtor: вика се АВТОМАТИЧНО когато обектът умира (край на {})
    ~Box() {}

    int get() const { return i; }

    void set(int x){this->i = x;};
};

int main() {
    Box a;        // default
    Box b(5);     // параметризиран
    Box c(b);     // copy  (c е ново; b си остава)

    Box d(b);
    d.set(9);
    std::cout << b.get() << ' ';

    std::cout << d.get();

    // c = b;     // assignment — друг механизъм, не copy ctor
}                 // ~Box за c, b, a (обратен ред на създаване)
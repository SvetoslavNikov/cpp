#include <iostream>

// Цел: да ВИДИШ copy ctor — кой е новият обект, кой е източникът.
class Box {
    int i;
public:
    Box(int x) : i(x) {
        std::cout << "  [ctor int]   this=" << this
                  << "  i=" << i << "\n";
    }

    // box = РЕФЕРЕНЦИЯ към оригинала (същият адрес като b)
    // this = адресът на НОВИЯ обект (c)
    Box(const Box& box) : i(box.i) {
        std::cout << "  [copy ctor]  this(NEW)=" << this
                  << "  &box(SOURCE)=" << &box
                  << "  copied i=" << i << "\n";
    }

    int get() const { return i; }
    void set(int x) { i = x; }
};

int main() {
    std::cout << "1) Box b(5);\n";
    Box b(5);
    std::cout << "   &b = " << &b << "\n\n";

    std::cout << "2) Box c(b);  // вика copy ctor\n";
    Box c(b);
    std::cout << "   &c = " << &c << "\n\n";

    std::cout << "3) След copy: b и c са РАЗДЕЛНИ обекти\n";
    std::cout << "   b.get()=" << b.get() << "  c.get()=" << c.get() << "\n";
    c.set(9);
    std::cout << "   c.set(9) => b.get()=" << b.get()
              << "  c.get()=" << c.get() << "\n";
    std::cout << "   (b не се променя — копирахме стойност, не вързахме двата)\n";
}

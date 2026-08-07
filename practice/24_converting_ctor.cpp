// ТЕМА 24 (част 1) — converting constructor
//
// Конструктор с 1 аргумент (не explicit) = „как да направя Type от друго нещо“.
// Компилаторът може ДА ГО ВИКНЕ МЪЛЧАЛИВО (implicit conversion).
//
//   void f(Meter m);
//   f(5);              // int → Meter чрез Meter(int)   ако НЕ е explicit
//
// explicit = „само явно“:
//   Meter m = 5;       // грешка
//   Meter m(5);        // OK
//   Meter m = Meter(5); // OK
//   static_cast<Meter>(5); // OK
//
// Защо explicit често е по-добре: случайни конверсии бъркат overload-и и ==.
//
#include <iostream>

class Meter {
    int m;
public:
    /*explicit*/ Meter(int m) : m(m) {}   // махни /* */ → счупи f(5) по-долу

    int get() const { return m; }

    friend std::ostream& operator<<(std::ostream& os, const Meter& x) {
        return os << x.m << "m";
    }
};

void printLen(Meter x) {
    std::cout << "len = " << x << "\n";
}

int main() {
    Meter a(10);          // директно — винаги OK
    std::cout << a << "\n";

    printLen(5);          // implicit: 5 → Meter(5)  (ако ctor НЕ е explicit)

    Meter b = 7;          // copy-init + converting ctor (пак implicit)
    std::cout << b << "\n";

    // С explicit Meter(int):
    //   printLen(5);     // грешка
    //   printLen(Meter(5)); // OK — явно
}

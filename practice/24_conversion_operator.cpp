// ТЕМА 24 (част 2) — conversion operator (операция-преобразуване)
//
// Обратното на converting ctor:
//   ctor:           чужд тип  →  моят тип     Meter(int)
//   conversion op:  моят тип  →  чужд тип     operator int() const
//
// Синтаксис:  operator TargetType() const { return ...; }
//   няма return type в декларацията — TargetType Е резултатът.
//
// Implicit conversion operator = компилаторът вика мълчаливо (опасно).
// explicit operator int() = само static_cast<int>(obj) / int(obj) явно.
//
// Изпит: и двете са „преобразувания“; explicit контролира implicit-а.
//
#include <iostream>

class Fraction {
    int num, den;
public:
    Fraction(int n, int d) : num(n), den(d) {}

    // Fraction → double  (за четене / смесена аритметика)
    explicit operator double() const {
        return static_cast<double>(num) / den;
    }

    // Fraction → bool  (типично: „има ли стойност / ненула?“)
    explicit operator bool() const {
        return num != 0;
    }

    friend std::ostream& operator<<(std::ostream& os, const Fraction& f) {
        return os << f.num << "/" << f.den;
    }
};

int main() {
    Fraction f(3, 4);
    std::cout << f << "\n";                         // 3/4

    double d = static_cast<double>(f);              // explicit → OK
    std::cout << d << "\n";                         // 0.75

    // double bad = f;                              // грешка: operator double е explicit

    if (f)                                          // context: explicit operator bool OK в if
        std::cout << "nonzero\n";

    Fraction z(0, 1);
    if (!z)
        std::cout << "zero\n";
}

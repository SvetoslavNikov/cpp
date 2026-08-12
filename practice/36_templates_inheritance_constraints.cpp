// ТЕМА 36 — templates + наследяване, specialization, ограничители
//
// 35 = "как се пише template".  36 = "как се СВИВА / ОГРАНИЧАВА".
//
// specialization = отделна версия за конкретен тип (или семейство типове)
// constraint     = "T трябва да умее X", иначе грешка рано и ясно
//
#include <iostream>
#include <type_traits>

// ── template + inheritance ──
template <typename T>
class Box {
protected:
    T value;
public:
    explicit Box(T v) : value(v) {}
    T get() const { return value; }
};

// LabeledBox "е" Box<T> + етикет
template <typename T>
class LabeledBox : public Box<T> {
    const char* label;
public:
    LabeledBox(T v, const char* lab) : Box<T>(v), label(lab) {}
    void print() const {
        std::cout << label << ": " << this->get() << "\n";
    }
};

/*
int main() {
    char c = 'c';
    LabeledBox<int> box{5, &c};
}*/

// ── specialization: друга версия САМО за bool ──
template <typename T>
struct Name { static void show() { std::cout << "generic\n"; } };

template <>
struct Name<bool> { static void show() { std::cout << "bool!\n"; } };

// ── constraint: T трябва да е число ──
template <typename T>
T twice(T x) {
    static_assert(std::is_arithmetic_v<T>, "T must be a number");
    return x + x;
}

int main() {
    LabeledBox<int> b(10, "score");
    b.print();                    // score: 10

    Name<int>::show();            // generic
    Name<bool>::show();           // bool!

    std::cout << twice(7) << "\n"; // 14
    // twice(std::string("x"));   // грешка: T must be a number
}

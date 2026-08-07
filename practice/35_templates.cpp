// ТЕМА 35 — генерични (пораждащи) типове: templates
//
// Идея: пишеш кода ВЕДНЪЖ с placeholder T; компилаторът ПОРАЖДА
// конкретна версия за всеки използван тип (compile-time).
//
//   template <typename T>   // или: template <class T>  — същото
//   T maxValue(T a, T b) { ... }
//
// Function template:  maxValue(3, 7)        → T = int (извличане)
//                     maxValue<double>(1, 2.5) → явно
// Class template:     Box<int> b(42);       → T почти винаги явно
//
// C++ templates ≠ .NET generics: тук кодът се генерира при компилация
// (почти „copy-paste“ за всеки тип), не runtime generic.
//
// Изпит: template е декларация; реалният код се появява при инстанция.
//
#include <iostream>
#include <string>

// ── 1) function template ──
template <typename T>
T maxValue(T a, T b) {
    return (a > b) ? a : b;
}

// два type-параметъра
template <typename T, typename U>
void printPair(T a, U b) {
    std::cout << a << " | " << b << "\n";
}

// ── 2) class template ──
template <typename T>
class Box {
    T value;
public:
    explicit Box(T v) : value(v) {}

    T get() const { return value; }
    void set(T v) { value = v; }
};

// class template с два типа
template <typename K, typename V>
class Pair {
    K key;
    V val;
public:
    Pair(K k, V v) : key(k), val(v) {}

    K getKey() const { return key; }
    V getValue() const { return val; }
};

// // член-функция дефинирана ИЗВЪН class template
// template <typename T>
// class Counter {
//     T n;
// public:
//     explicit Counter(T start = T{}) : n(start) {}
//     void add(T amount);
//     T get() const { return n; }
// };
//
// template <typename T>
// void Counter<T>::add(T amount) {
//     n = n + amount;
// }
//
// int main() {
//     // function template — deduction
//     std::cout << maxValue(10, 20) << "\n";                 // 20  (T = int)
//     std::cout << maxValue(2.5, 1.1) << "\n";               // 2.5 (T = double)
//
//     // явно, когато типовете не съвпадат
//     std::cout << maxValue<double>(1, 2.5) << "\n";         // 2.5
//     // maxValue(1, 2.5);                                   // грешка: int ≠ double
//
//     printPair(42, std::string("answer"));                  // T=int, U=string
//     printPair(std::string("pi"), 3.14);
//
//     // class template — типът се пише изрично
//     Box<int> bi(100);
//     Box<std::string> bs("candy");
//     std::cout << bi.get() << "\n";                         // 100
//     std::cout << bs.get() << "\n";                         // candy
//     bi.set(200);
//     std::cout << bi.get() << "\n";                         // 200
//
//     Pair<std::string, int> p("age", 21);
//     std::cout << p.getKey() << " => " << p.getValue() << "\n";
//
//     Counter<int> c(5);
//     c.add(3);
//     std::cout << c.get() << "\n";                          // 8
// }

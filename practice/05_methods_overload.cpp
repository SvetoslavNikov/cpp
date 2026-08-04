// ТЕМА 5: Методи = поведение (instance; const; public/private; static = на класа, без this).
// Overload = същото име, различна сигнатура: параметри И/ИЛИ const върху метода.
// Override ≠ overload (override = наследяване). Само различен return type ≠ overload.
#include <iostream>

class Calc {
public:
    // --- overload по параметри ---
    int add(int a, int b) { return a + b; }              // (int, int)
    double add(double a, double b) { return a + b; }     // (double, double)
    int add(int a, int b, int c) { return a + b + c; }   // (int, int, int)

    // --- overload по const (един и същ списък параметри!) ---
    // non-const обект → предпочита non-const версията
    // const обект     → само const версията
    void who() { std::cout << "non-const method\n"; }
    void who() const { std::cout << "const method\n"; }

    int value() const { return 42; }  // const: не променя обекта
    // static int id() { return 1; }  // Calc::id() — без обект, без this
};

int main() {
    Calc c;
    const Calc cc;

    std::cout << c.add(1, 2) << "\n";        // int overload
    std::cout << c.add(1.5, 2.5) << "\n";    // double overload
    std::cout << c.add(1, 2, 3) << "\n";     // 3-arg overload

    c.who();    // non-const method
    cc.who();   // const method  ← интересното: overload по const
}

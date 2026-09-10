// ТЕМА 15: Подклас (subtype) може да се ползва като базовия (is-a).
// Vehicle& / const Vehicle&
// приемат и Car.
//
// Копие по стойност реже до базовия тип (slicing). Обратното (базов → производен) не.
#include <iostream>

class Vehicle {
public:
    void move() const { std::cout << "move\n"; }
};

class Car : public Vehicle {
public:
    void honk() const { std::cout << "beep\n"; }
};

void drive(const Vehicle& v) {                    // параметър: референция към базов тип
    v.move();                                     // OK за Vehicle и Car
    // v.honk();                                  // НЕ: през Vehicle& няма Car методи
}

int main() {
    Car c;
    Vehicle& r = c;                               // OK: Car „е“ Vehicle
    r.move();
    // r.honk();                                  // НЕ

    drive(c);                                     // OK: subtype → basetype параметър
    drive(r);

    // Vehicle v = c;                             // slicing: копира само Vehicle частта — избягвай
    // void park(const Car&); park(Vehicle{});    // НЕ: не всеки Vehicle е Car
}

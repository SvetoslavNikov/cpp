// ТЕМА 8: Класова йерархия = is-a (общо в base, специфично в derived). public наследяване.
// has-a / колекция ≠ наследяване. explicit = ctor-ът не прави скрита конверсия от 1 аргумент.
#include <iostream>

class Vehicle {                               // общото
protected:
    int wheels;
public:
    explicit Vehicle(int w) : wheels(w) {}
    int getWheels() const { return wheels; }
};

class Car : public Vehicle {                  // Car Е Vehicle
public:
    explicit Car(int w) : Vehicle(w) {}
    void openTrunk() const { std::cout << "Trunk open\n"; }
};

class Bike : public Vehicle {                 // Bike Е Vehicle
public:
    explicit Bike(int w) : Vehicle(w) {}
    void ringBell() const { std::cout << "Ring!\n"; }
};

int main() {
    Car c(4);
    Bike b(2);
    c.openTrunk();
    b.ringBell();
    std::cout << c.getWheels() << " " << b.getWheels() << "\n";
}

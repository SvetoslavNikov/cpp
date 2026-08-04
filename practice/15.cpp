#include <iostream>


class Vehicle {
public:
    int wheels = 23;

    void move() const {
        std::cout << "the vehicle is moving";
    }
};


class Car : public Vehicle {
public:
    int wheels;

    Car(int i) : wheels(i) {
    }

    void honk() const { std::cout << "beep\n" << this->wheels; }
};

void drive(const Vehicle &v) {
    v.move();
}

int main() {
    Car c(5);

    Vehicle &r = c;

    std::cout << c.wheels;
    std::cout << r.wheels;
    drive(c);
    drive(r);


}

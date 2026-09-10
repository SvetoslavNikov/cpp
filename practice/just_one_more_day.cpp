#include <iostream>
#include <memory>
#include <string>
#include <utility>

using namespace std;

class Vehicle {
public:
    Vehicle() {
        cout<<"vehicle constructor called"<<endl;
    }
    virtual void honk() const = 0;

    virtual ~Vehicle() {
        cout<<"vehicle destructor called"<<endl;
    }
};

class Car : public Vehicle {
public:
    Car() {
        cout<<"car constructor called";
    }
    void honk() const override { cout << "car\n"; }
    ~Car() { cout << "Car destructor\n"; }
};

Vehicle& destroy(Vehicle& vehicle) {
    Car c = vehicle;
    return c;
}

int main() {

    Car c{};
    Vehicle& v = c;
    cout<<"hey";
    Vehicle& x = destroy(v);

}
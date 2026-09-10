
// 16_virtualization.cpp
//
// The short version:
//   stack object = usually destroyed automatically when its scope ends
//   heap object  = lives until somebody releases it
//   destructor   = cleanup code that runs when an object dies
//   virtual destructor = necessary when deleting a derived object through a
//                        base-class pointer
//
// You do not need to understand the compiler in detail yet. The compiler
// turns your declarations into storage and inserts calls to destructors at
// the appropriate points. The important question is: who owns the object,
// and who is responsible for its lifetime?

#include <iostream>
#include <memory>
#include <string>
#include <utility>

using namespace std;

class Marker {
    string name;

public:
    explicit Marker(string name) : name(std::move(name)) {
        cout << "constructed " << this->name << '\n';
    }

    ~Marker() {
        cout << "destroyed    " << name << '\n';
    }
};

void stack_example() {
    cout << "\n--- stack example ---\n";
    Marker local("local");
    cout << "function is still running\n";
} // local's destructor runs here automatically.

void heap_example() {
    cout << "\n--- heap example ---\n";
    Marker* raw = new Marker("heap object");
    cout << "new returned an address: " << raw << '\n';
    delete raw; // Destructor runs here, then the memory is released.
}

void leak_example() {
    cout << "\n--- intentional memory leak ---\n";
    Marker* leaked = new Marker("leaked object");
    cout << "We lose the only address: " << leaked << '\n';
    // There is no delete here. The object and its memory remain allocated
    // until the operating system ends the process. The destructor does not
    // run. This is a memory leak.
}

// Resource Acquisition Is Initialization (RAII): put ownership in an object.
// unique_ptr automatically performs delete when its scope ends.
void recommended_heap_example() {
    cout << "\n--- recommended heap example ---\n";
    auto safe = make_unique<Marker>("owned by unique_ptr");
    cout << "no manual delete is needed\n";
} // unique_ptr is destroyed, then it deletes Marker.

class Vehicle {
public:
    virtual void honk() const = 0;
    virtual ~Vehicle() = default;
};

class Car : public Vehicle {
public:
    void honk() const override { cout << "car\n"; }
    ~Car() override { cout << "Car destructor\n"; }
};

void polymorphism_example() {
    cout << "\n--- virtual destructor ---\n";
    Vehicle* vehicle = new Car;
    vehicle->honk();
    delete vehicle;
    // Because Vehicle::~Vehicle is virtual, delete calls ~Car first and
    // then ~Vehicle. Without it, deleting through Vehicle* is unsafe.
}

int main(int argc, char* argv[]) {
    stack_example();
    heap_example();
    recommended_heap_example();
    polymorphism_example();

    // Run with the argument "leak" to intentionally leak one object:
    //   ./16_virtualization leak
    // Leak detectors such as AddressSanitizer can report it:
    //   clang++ -std=c++17 -g -fsanitize=address 16_virtualization.cpp
    //   ./a.out leak
    if (argc > 1 && string(argv[1]) == "leak") {
        leak_example();
    }
}

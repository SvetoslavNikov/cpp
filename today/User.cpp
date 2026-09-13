#include <iostream>

class Animal { public:
    int a;
    virtual void sound() { std::cout << "..."; } virtual ~Animal() = default; };
class Dog : public Animal { public:
    int b;
    void sound() override { std::cout << "Woof"; } };

int main() {
    Dog d;
    Animal& a = d;   // референция към базовия тип - няма slicing
    a.sound();
    d.b;
    d.a;// извиква Dog::sound() - полиморфизъм

    Animal byValue = d; // тук ИМА slicing - byValue е чист Animal
    byValue.sound();     // "..."
    byValue.a;
    
}
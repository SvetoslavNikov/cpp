// ТЕМА 2: Данновите членове = състояние на обекта; методите = поведение. Параметърът е
// „дупката“ в дефиницията; аргументът е реалната стойност при извикване. (Пропърти ≈ get/set.)
#include <iostream>
#include <string>

class Person {
public:
    std::string name;   // даннов член
    int age;            // даннов член

    void setAge(int newAge) { age = newAge; }           // параметър: newAge
    void greet(std::string who) {                       // параметър: who
        std::cout << name << " -> " << who << "\n";
    }
};

int main() {
    Person p;
    p.name = "Jack";
    p.setAge(24);          // аргумент 24
    p.greet("Maria");      // аргумент "Maria"
    std::cout << p.age << "\n";
}

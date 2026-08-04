// ТЕМА 4: Accessor (getter) чете състоянието без да го променя; mutator (setter) го променя —
// често с валидация. Заедно пазят капсулацията: отвън няма директен достъп до полетата.
#include <iostream>
#include <string>

class Person {
private:
    std::string name;
    int age;
public:
    std::string getName() const { return name; }   // accessor
    int getAge() const { return age; }             // accessor (+ const = не променя обекта)

    void setName(std::string n) { name = n; }      // mutator
    void setAge(int a) { if (a >= 0) age = a; }    // mutator + проверка
};

int main() {
    Person p;
    p.setName("Jack");
    p.setAge(24);
    std::cout << p.getName() << " " << p.getAge() << "\n";
}

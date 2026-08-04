// ТЕМА 3: public = достъп отвсякъде; private = само вътре в класа; protected = клас + наследници.
// Капсулация: криеш данните (private), даваш контролиран интерфейс (public методи).
#include <iostream>

class Person {
private:
    int age;                              // скрито отвън
protected:
    int id;                               // за наследници (по-късно)
public:
    void setAge(int a) { if (a >= 0) age = a; }
    int  getAge() const { return age; }
};

int main() {
    Person p;
    // p.age = 5;                         // ГРЕШКА: private
    p.setAge(24);
    std::cout << p.getAge() << "\n";
}

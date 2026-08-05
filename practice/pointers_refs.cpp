// & и * (не е отделна тема от конспекта): & в ТИП = референция (друго име);
// & като операция = адрес. * в ТИП = указател; * като операция = стойността на адреса.
#include <iostream>
#include <string>

class Employee {
    std::string name;
public:
    explicit Employee(const std::string& n) : name(n) {}
    std::string getName() const { return name; }
};

void byRef(int& n) { n++; }                       // Type& = референция; викаш byRef(x)
void byPtr(int* p) { (*p)++; }                    // Type* = указател; викаш byPtr(&x)

void printEmp(const Employee& e) {                // референция към обект — без *
    std::cout << e.getName() << "\n";
}

int main() {
    int x = 10;
    int& ref = x;                                 // ref Е x
    ref = 20;                                     // x == 20

    int* p = &x;                                  // &x = адрес; p пази адреса
    *p = 30;                                      // *p = стойността на адреса → x == 30
    std::cout << x << " " << *p << "\n";

    byRef(x);                                     // подаваш обекта
    byPtr(&x);                                    // подаваш адреса
    std::cout << x << "\n";                       // 32

    Employee e("Ana");
    Employee* ep = &e;
    printEmp(e);                                  // const Employee&
    std::cout << ep->getName() << "\n";           // през указател: ->  (също (*ep).getName())
}

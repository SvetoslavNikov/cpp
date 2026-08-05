// ТЕМА 14: Вертикално = is-a (наследяване). Хоризонтално = knows/has/uses.
// Association/aggregation: връзка с указател, животът е отвън. Composition: член-обект, умира с цялото.
#include <iostream>
#include <string>
#include <vector>

class Employee {                                  // независим обект
    std::string name;
public:
    explicit Employee(const std::string& n) : name(n) {}
    std::string getName() const { return name; }
};

class Engine {                                    // част за composition
    int hp;
public:
    explicit Engine(int h) : hp(h) {}
    int getHp() const { return hp; }
};

class Car {                                       // composition: Car ИМА Engine (не Е Engine)
    Engine eng;
    std::string model;
public:
    Car(std::string m, int hp) : eng(hp), model(m) {}
    void info() const { std::cout << model << " " << eng.getHp() << "hp\n"; }
};

class Team {                                      // aggregation: Team държи указатели, не притежава живота
    std::vector<Employee*> members;
public:
    void add(Employee* e) { members.push_back(e); }
    void list() const {
        for (Employee* e : members) std::cout << e->getName() << "\n";
    }
};

int main() {
    Car c("Golf", 150);                           // Engine се ражда/умира с Car
    c.info();

    Employee a("Ana"), b("Bob");                  // живеят сами
    Team t;
    t.add(&a);                                    // & = адрес (aggregation)
    t.add(&b);
    t.list();                                     // Team само „ползва“ Employee
}

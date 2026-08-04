#include <iostream>
#include <string>
#include <vector>

using namespace std;

class employee {
    string name;
public:
    employee(const string& name) : name(name){}

    string getName() {
        return this->name;
    }
};

class lys {
    vector<employee*> employees;
public:
    lys(){};

    void addEmployee(employee* employee) {
        employees.push_back(employee);
    }

    employee* getEmployee(employee* emp) const {
        for (auto it = employees.begin(); it != employees.end(); ++it) {
            if (*it == emp) {
                return *it;
            }
        }
        return nullptr;
    }
};

int main() {
    lys l;
    employee e("hey");
    l.addEmployee(&e);

    employee* p = l.getEmployee(&e);
    if (p) {
        std::cout << p->getName() << "\n";
    }
}
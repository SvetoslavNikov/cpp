#include<iostream>
#include<memory>
#include<string>

class User {
    std::string name;
public:
    explicit User(std::string n): name(std::move(n)) {

    }

    void hello() const {std::cout<<name<<'\n';}

    ~User() {
        std::cout<<"hey little f";
    }
};

void createUser() {
    auto p = std::make_unique<User>("Maria");
}

int main() {
 createUser();
    //double free
    //use after free
    //memory leak

}
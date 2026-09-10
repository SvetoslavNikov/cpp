#include "User.hpp"

#include <iostream>

User::User(const std::string& name)
    : name(name) {
    std::cout << "Constructing " << this->name << '\n';
}

User::~User() {
    std::cout << "Destroying " << name << '\n';
}

void User::hello() const {
    std::cout << "Hello, " << name << "!\n";
}

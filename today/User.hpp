#pragma once

#include <string>

class User {
public:
    explicit User(const std::string& name);
    ~User();

    void hello() const;

private:
    std::string name;
};

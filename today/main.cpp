#include "User.hpp"

int main() {
    User first("Ivan");
    first.hello();

    {
        User second("Maria");
        second.hello();
    } // second is destroyed here

    return 0;
} // first is destroyed here

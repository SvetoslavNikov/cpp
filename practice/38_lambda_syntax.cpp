// ТЕМА 38 — синтаксис на lambda (C++)
//
//   [capture] (params) { body }
//
// capture:
//   []      нищо
//   [x]     копие на x
//   [&x]    референция към x  (променя оригинала)
//   [=]     копирай всичко
//   [&]     референция към всичко
//
// mutable = позволи промяна на КОПИЕТО (не на външната променлива)
//
#include <iostream>

int main() {
    int x = 5;

    auto a = [] { return 1; };               // []  без capture
    auto b = [x] { return x + 1; };          // [x] копие
    auto c = [&x] { x = 100; return x; };    // [&x] пипа оригинала

    std::cout << a() << "\n";                // 1
    std::cout << b() << "\n";                // 6  (копие беше 5)
    std::cout << c() << "\n";                // 100
    std::cout << "x=" << x << "\n";          // 100

    // mutable: ++ върху копието; външният y не се сменя
    int y = 0;
    auto d = [y]() mutable { return ++y; };
    std::cout << d() << " " << d() << "\n";  // 1 2
    std::cout << "y=" << y << "\n";          // 0

    // generic lambda (C++14): auto параметри
    auto maxv = [](auto a, auto b) { return a > b ? a : b; };
    std::cout << maxv(3, 9) << "\n";         // 9
}

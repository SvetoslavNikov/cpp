// ТЕМА 37 — 3 начина да подадеш "действие" (callable)
//
// 1) function pointer — адрес на функция; БЕЗ памет/state
// 2) functor          — клас с operator(); МОЖЕ state (член k)
// 3) lambda           — същият functor, но написан на мястото
//
// Защо lambda: по-кратко, кодът е до sort/count_if, capture вместо struct.
//
#include <iostream>
#include <vector>
#include <algorithm>

int add(int a, int b) { return a + b; }

// functor = обект, който се вика като функция
struct Times {
    int k;
    int operator()(int x) const { return x * k; }
};

int main() {

    int x = 10;
    int c = 11;
    // 1) pointer
    auto a = [&x](int a, int b) {
        x=x+124;
        return a+b+x;
    };

    a(1,2);

    std::cout<<x;
}

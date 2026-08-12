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
    // 1) pointer
    int (*fp)(int, int) = add;
    std::cout << fp(2, 3) << "\n";           // 5

    // 2) functor
    Times t{10};
    std::cout << t(3) << "\n";               // 30

    // 3) lambda (най-често в STL)
    std::vector<int> v{1, 2, 3, 4};
    int n = std::count_if(v.begin(), v.end(),
                          [](int x) { return x % 2 == 0; });
    std::cout << n << "\n";                  // 2 (2 и 4)

    // state: functor → член; lambda → [capture]
    int k = 10;
    auto scale = [k](int x) { return x * k; };
    std::cout << scale(3) << "\n";           // 30
}

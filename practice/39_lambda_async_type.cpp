  // ТЕМА 39 — тип на lambda + lambda в async
//
// ТИП: всеки []{...} е УНИКАЛЕН анонимен тип → пазиш с auto
//      два еднакви на вид lambda ≠ един тип
//      общ тип за "кутия": std::function<R(Args...)>
//
// ASYNC: std::async + lambda; future.get() чака резултата
//        capture by value [x] = безопасно
//        capture by ref  [&x] = x трябва да ЖИВЕЕ до get()
//
#include <iostream>
#include <future>
#include <functional>

int main() {
    // тип
    int (*add)(int, int)= [](int a, int b) { return a + b; };
    auto add2 = [](int a, int b) { return a + b; };
    // add = add2;                           // ГРЕШКА: различни типове
    std::cout << add(2, 3) << "\n";          // 5

    std::function<int(int, int)> op = add;   // "общ" тип
    std::cout << op(3, 3) << "\n"; //6
    op = [](int a, int b) { return a * b; };
    std::cout << op(2, 3) << "\n";           // 6

    // async + lambda
    auto fut = std::async(std::launch::async, [] {
        return 40 + 2;
    });
    std::cout << fut.get() << "\n";          // 42  (чака)

    // безопасно: копие на x
    int x = 10;
    auto fut2 = std::async(std::launch::async, [&x] mutable { x = x+1; return x; });
    std::cout << fut2.get() << "\n";         // 20
    std::cout << x << std::endl;
}

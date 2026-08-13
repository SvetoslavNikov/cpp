// ТЕМА 40 — thread, async, кой "притежава" нишката
//
// std::thread t(f);  t.join();   // стартирай + ЧАКАЙ края
//   забрави join/detach → програмата гърми (terminate)
//
// thread е move-only:  t2 = std::move(t1);  // t1 вече празен
//
// std::async → future;  f.get() = резултатът (блокира до готов)
//
#include <iostream>
#include <thread>
#include <future>

void hello(int id) {
    std::cout << "hi from " << id << "\n";
}

int main() {
    // 1) thread + join (задължително)
    std::thread t1(hello, 1);
    t1.join();

    // 2) lambda на нишка
    std::thread t2([] { std::cout << "lambda thread\n"; });
    t2.join();

    // 3) ownership = move
    std::thread a([] { std::cout << "moved\n"; });
    // std::thread b = a; error
    std::thread b = std::move(a);            // a вече НЕ държи нишка
    // a.join();                             // грешка
    b.join();

    // 4) async = задача + future
    std::future<int> f = std::async(std::launch::async, [] {
        return 40 + 2;
    });
    std::cout << "main works...\n";
    std::cout << f.get() << "\n";            // 42
}

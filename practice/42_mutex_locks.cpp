// ТЕМА 42 — mutex = ключалка (само 1 нишка в критичната секция)
//
//   std::mutex m;
//   std::lock_guard<std::mutex> lock(m);  // заключи
//   // ... критична секция ...
//   // отключи автоматично в края на блока (RAII)
//
// ползвай mutex когато няколко стъпки трябва да са "като една"
// (примерно: if (balance >= x) balance -= x;)
//
#include <iostream>
#include <thread>
#include <mutex>

int counter = 0;
std::mutex m;

void worker() {
    for (int i = 0; i < 100000; ++i) {
        std::lock_guard<std::mutex> lock(m);  // заключи
        counter++;                            // само аз пипам counter
    }                                         // отключи
}

int balance = 100;
std::mutex bal_m;

void withdraw(int amount) {
    std::lock_guard<std::mutex> lock(bal_m);
    if (balance >= amount)        // check
        balance -= amount;        // act   ← двете под един lock
}

int main() {
    std::thread t1(worker), t2(worker);
    t1.join(); t2.join();
    std::cout << "counter: " << counter << "\n";  // 200000

    std::thread w1(withdraw, 80), w2(withdraw, 80);
    w1.join(); w2.join();
    std::cout << "balance: " << balance << "\n";  // 20 (само 1 теглене)
}

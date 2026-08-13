// ТЕМА 41 — data race vs atomic
//
// Две нишки пишат plain int без sync → UB (често "губим" ++).
// std::atomic<int>:  ++ / load / store са безопасни.
//
// atomic = една проста стойност
// mutex  = много стъпки заедно (тема 42)
//
#include <iostream>
#include <thread>
#include <atomic>

int plain = 0;
std::atomic<int> safe{0};

void race() {
    for (int i = 0; i < 100000; ++i) plain++;
}

void ok() {
    for (int i = 0; i < 100000; ++i) safe++;
}

int main() {
    // race — резултатът често < 200000 (UB, само за demo)
    std::thread r1(race), r2(race);
    r1.join(); r2.join();
    std::cout << "plain:  " << plain << "  (искаме 200000)\n";

    // atomic — винаги 200000
    std::thread a1(ok), a2(ok);
    a1.join(); a2.join();
    std::cout << "atomic: " << safe << "\n"; // 200000
}

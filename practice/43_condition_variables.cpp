// ТЕМА 43 — condition_variable = "чакай до сигнал, не върти CPU"
//
// waiter:   cv.wait(lock, predicate);   // спи, докато predicate е true
// signaler: смени данните под mutex → cv.notify_one();
//
// ТРЯБВА unique_lock (не lock_guard) — wait отключва mutex-а докато спи.
// Винаги с predicate: защита от "събуди се без причина".
//
/*
consumer:  lock → ready? NO → unlock + sleep
                                  ↓
producer:  lock → ready = true → unlock → notify
                                               ↓
consumer:       wake → lock → ready? YES → continue
 */
#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <chrono>

std::mutex m;
std::condition_variable cv;
bool ready = false;
int data = 0;

void consumer() {
    std::unique_lock<std::mutex> lock(m);
    cv.wait(lock, [] { return ready; });   // спи до ready == true
    std::cout << "got " << data << "\n";   // 42
}

void producer() {
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    {
        std::lock_guard<std::mutex> lock(m);
        data = 42;
        ready = true;
    }
    cv.notify_one();                       // събуди consumer
}

int main() {
    std::thread c(consumer);
    std::thread p(producer);
    c.join();
    p.join();
}

#include <condition_variable>
#include <mutex>
#include <thread>
#include <iostream>

std::mutex m;
std::condition_variable cv;
bool ready = false;

void consumer(int id) {
    std::unique_lock<std::mutex> lock(m);

    std::cout << "C" << id << ": ready = " << ready << "\n";

    std::cout << "C" << id << ": waiting...\n";

    cv.wait(lock, [] { return ready; });

    // wait() woke up AND reacquired the mutex
    std::cout << "C" << id << ": woke up, ready = "
              << ready << "\n";

    std::cout << "C" << id << ": Consumed\n";
}

void producer() {
    {
        std::lock_guard<std::mutex> lock(m);

        std::cout << "P: setting ready = true\n";
        ready = false;
    } // mutex released

    std::cout << "P: notify_all()\n";
    cv.notify_one();
}

int main() {
    std::thread c(consumer, 1);
    std::thread c1(consumer, 2);
    std::thread p(producer);

    c.join();
    c1.join();
    p.join();
}
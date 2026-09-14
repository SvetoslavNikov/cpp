// ТЕМА 42 — Context при асинхронни изчисления
//          и управление на превключванията на Context
//
// В C++ няма SynchronizationContext като в C#.
//
// Execution context в C++ обикновено означава:
//     - коя нишка изпълнява кода
//     - кой scheduler/thread pool изпълнява задачата
//     - какво е състоянието на изпълнението
//     - как се предава работата между нишките
//
// std::async може да изпълни функцията асинхронно
// на друга нишка:
//
//     main thread
//          |
//          | std::async
//          v
//     worker thread
//          |
//          | result
//          v
//     future.get()
//
// Важно:
// std::future::get() НЕ връща execution context.
// Той просто изчаква и получава резултата.
//
// C++ стандартната библиотека няма директен:
//     await
//     SynchronizationContext
//     ConfigureAwait(false)
//
// Ако искаме контрол върху това КЪДЕ се изпълнява кодът,
// използваме например:
//     std::thread
//     thread pool
//     собствен scheduler
//     task system
//
// Context switch:
//     Thread A → Thread B
//
// Операционната система може да превключва между нишки.
// Това не трябва да се бърка с async операция.
//
// async ≠ задължително context switch
//
// Една async операция може да:
//     - използва друга нишка
//     - използва същата нишка по-късно
//     - бъде deferred
//     - използва thread pool според конкретния механизъм
//
// В стандартния C++20 няма универсален async/await механизъм.
// C++20 има coroutines, чрез които могат да се изграждат
// async/await-подобни конструкции.

#include <iostream>
#include <future>
#include <thread>
#include <chrono>

void work(int id) {

    std::cout
        << "work " << id
        << " on thread "
        << std::this_thread::get_id()
        << "\n";

    std::this_thread::sleep_for(
        std::chrono::milliseconds(500)
    );
}

int main() {

    // 1) main thread
    std::cout
        << "main thread: "
        << std::this_thread::get_id()
        << "\n";


    // 2) async task
    std::future<void> f =
        std::async(
            std::launch::async,
            work,
            1
        );


    // 3) Main thread продължава да работи
    std::cout << "main continues...\n";


    // 4) get() изчаква task-а
    //
    // Ако work() още не е приключил,
    // текущата нишка ще блокира тук.
    f.get();


    // 5) std::thread дава директен контрол
    //
    // Създаваме worker thread.
    std::thread t([] {

        std::cout
            << "worker thread: "
            << std::this_thread::get_id()
            << "\n";

    });

    // join() чака worker thread-а.
    t.join();


    // 6) Context switch
    //
    // Възможно изпълнение:
    //
    // Main Thread
    //     |
    //     | std::async
    //     v
    // Worker Thread
    //     |
    //     | изпълнява work()
    //     v
    // Task finished
    //     |
    //     v
    // future.get()
    //
    // Операционната система управлява
    // превключването между нишките.


    // 7) Важно разграничение
    //
    // std::async:
    //     задача + future
    //
    // std::thread:
    //     директно създадена нишка
    //
    // future.get():
    //     чака резултата
    //
    // context switch:
    //     превключване на изпълнението между нишки
    //
    // async операция НЕ означава автоматично
    // context switch.
}
// ТЕМА 41 — async, await, тип на await
//
// C++ НЯМА вграден async/await синтаксис като C#.
//
// Вместо:
//     async Task<int> f()
//     await f();
//
// C++ използва:
//     std::async(...)
//     std::future<T>
//     future.get()
//
// std::async → стартира асинхронна задача
// std::future<T> → представлява бъдещия резултат
// future.get() → изчаква резултата и го връща
//
// Типът на резултата зависи от функцията:
//
// int f()                 → std::future<int>
// std::string f()         → std::future<std::string>
// void f()                → std::future<void>
//
// Важно:
// get() е аналогичен по идея на await:
//     - ако резултатът е готов → взима го веднага
//     - ако не е готов → блокира, докато стане готов
//
// C++ няма:
//     async Task<T>
//     async void
//
// Вместо това:
//     std::future<T>
//     std::future<void>

#include <iostream>
#include <future>
#include <string>

// 1) Функция с резултат
int calculate() {
    return 40 + 2;
}

// 2) Функция, която връща string
std::string get_name() {
    return "John";
}

// 3) Функция без резултат
void work() {
    std::cout << "work finished\n";
}

int main() {

    // 4) async + future<int>
    std::future<int> f =
        std::async(std::launch::async, calculate);

    std::cout << "main works...\n";

    int result = f.get();
    std::cout << result << "\n";        // 42


    // 5) future<string>
    std::future<std::string> name = std::async(std::launch::async, get_name);

    std::cout << name.get() << "\n";    // John


    // 6) future<void>
    std::future<void> task =
        std::async(std::launch::async, work);

    task.get();                         // чакай края


    // 7) std::launch::async
    //
    // Изисква асинхронно изпълнение.
    //
    // std::async(std::launch::async, f)
    //
    // задачата се изпълнява независимо от текущия поток.


    // 8) Без launch::async
    //
    // std::async(f)
    //
    // оставя implementation-а да избере:
    //
    //     std::launch::async
    // или
    //     std::launch::deferred
    //
    // Затова, когато искаме реално асинхронно изпълнение,
    // използваме:
    //
    // std::async(std::launch::async, f);


    // 9) Няма async void като отделен C++ механизъм.
    //
    // За void функция:
    //
    // void work();
    //
    // получаваме:
    //
    // std::future<void>
    //
    // чрез:
    //
    // std::async(std::launch::async, work);
}
// ТЕМА 46 — co_await; тип; Task vs void
//
// функция с co_await / co_return / co_yield = coroutine
// co_await expr  = пауза тук ако expr не е готов; НЕ пуска нишка
//
// co_await иска 3 метода. Типът на израза = типът на await_resume():
struct Awaitable {
    bool await_ready();                       // true → без пауза
    void await_suspend(std::coroutine_handle<>); // пауза
    int  await_resume();                      // co_await → int
};
// ЗАЩО: линеен код вместо callback; compiler прави state machine
//
// Task<T> f() { T x = co_await g(); co_return x; }  // може co_await; грешка в Task
// void    h() { co_await g(); }                    // не се чака; грешка = terminate
//
#include <coroutine>
int main() {}

// ТЕМА 22 (част 1) — friend function
//
// private = заключено. friend function = ЕДНА свободна функция с ключ.
//
// Кога има смисъл (не „можехме ли getter“):
//   функцията НЕ е естествен метод на ЕДИН обект, но трябва private
//   (класика: operator<<, или функция между ДВА класа).
//
// friend НЕ е член → викаш canPay(w, b), НЕ w.canPay(b).
//
#include <iostream>

class Bill;   // „Bill съществува“ — пълната дефиниция по-долу

class Wallet {
    int money;
public:
    explicit Wallet(int m) : money(m) {}
    friend bool canPay(const Wallet& w, const Bill& b);
};

class Bill {
    int amount;
public:
    explicit Bill(int a) : amount(a) {}
    friend bool canPay(const Wallet& w, const Bill& b);  // същият подпис!
};

bool canPay(const Wallet& w, const Bill& b) {
    return w.money >= b.amount;   // OK само заради friend
}

int main() {
    Wallet w(25);
    Bill b(10);
    std::cout << (canPay(w, b) ? "yes\n" : "no\n");   // yes
}

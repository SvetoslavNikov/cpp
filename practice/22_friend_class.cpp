// ТЕМА 22 (част 3) — friend class
//
// friend function = ключ за ЕДНА функция
// friend class    = ключ за ВСИЧКИ методи на този клас
//
// BankAccount крие cash. Само BankOwner може да го чете директно.
// main / чужди функции — не (освен през public API, ако има).
//
// BankOwner owner;   → обект
// BankOwner owner(); → НЕ обект (декларация на функция)
//
#include <iostream>

class BankAccount {
    int cash;
public:
    explicit BankAccount(int i) : cash(i) {}
    friend class BankOwner;   // целият клас е доверен
};

class BankOwner {
public:
    void checkAccount(const BankAccount& account) {
        // OK: BankOwner е friend → вижда private cash
        std::cout << "Bank account " << account.cash << "\n";
    }
};

int main() {
    BankOwner owner;              // обект (БЕЗ празни ())
    BankAccount account(3);
    owner.checkAccount(account);  // Bank account 3
}

// ТЕМА 13 (част 2) — само ДЕСТРУКТОРИ + какво е delete
//
// Деструктор ~Box() се вика АВТОМАТИЧНО когато обектът умира (край на {}).
//
// КОГА ПИШЕШ СВОЙ ~T():
//   НЕ — само int/string/vector… (чистят се сами)
//   ДА — ти си взел памет с new → ТРЯБВА да я върнеш с delete
//
// new / delete (минимум):
//   int* p = new int[3];   // „дай ми 3 int-а от динамичната памет“, p = адресът им
//   delete[] p;            // „връщам тази памет“ — задължително, иначе ИЗТИЧАНЕ (leak)
//   new int     ↔ delete p
//   new int[n]  ↔ delete[] p     // масив → delete[]  (с квадратни скоби)
//
// В клас: new в конструктора → delete в деструктора (автоматично при смъртта на обекта).
//
#include <iostream>

// --- A) Само да ВИДИШ кога се вика dtor (без new/delete) ---
class Tracer {
public:
    Tracer()  { std::cout << "  Tracer ctor\n"; }
    ~Tracer() { std::cout << "  Tracer dtor  ← обектът умира\n"; }
};

// --- B) Реална нужда от dtor: класът държи памет от new ---
class Buffer {
    int* data;   // адрес на масив, който НИЕ взехме с new
    int  n;
public:
    explicit Buffer(int size) : n(size) {
        data = new int[size];             // 1) вземи памет
        for (int i = 0; i < n; ++i) data[i] = i;
        std::cout << "  Buffer: new[] " << n << " ints, data=" << data << "\n";
    }

    ~Buffer() {
        std::cout << "  Buffer: delete[] data\n";
        delete[] data;                    // 2) върни СЪЩАТА памет
        data = nullptr;                   // (добра практика: указателят вече не сочи валидно)
    }

    void print() const {
        std::cout << "  data: ";
        for (int i = 0; i < n; ++i) std::cout << data[i] << " ";
        std::cout << "\n";
    }

    Buffer(const Buffer&)            = delete;  // засега без копие (иначе 2 delete на едно)
    Buffer& operator=(const Buffer&) = delete;
};

int main() {
    std::cout << "1) Tracer — dtor при край на block\n";
    {
        Tracer t;
    }   // тук ~Tracer()

    std::cout << "2) Buffer — new в ctor, delete в dtor\n";
    {
        Buffer b(3);
        b.print();
    }   // тук ~Buffer() → delete[]

    std::cout << "done\n";
}

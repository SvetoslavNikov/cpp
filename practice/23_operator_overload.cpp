// ТЕМА 23 (част 1) — припокриване на оператори: същност + ограничения
//
// Същност: даваш смисъл на +, ==, << … за ТВОИ типове.
//   a + b  →  a.operator+(b)   или   operator+(a, b)
// Overload на метод (тема 5) ≠ overload на оператор — същото име, различни правила.
//
// ОГРАНИЧЕНИЯ (изпит / практика):
//   • не изобретяваш нови символи (няма operator**)
//   • не сменяш приоритет, асоциативност, брой операнди
//   • не overload:  ::   .   .*   ?:   (и sizeof/typeid/… — не са „твои“ ops)
//   • поне един операнд = потребителски тип (не 1+2 чрез твой operator+)
//   • =  []  ()  ->   ТРЯБВА да са членове (member)
//   • << >> често free + friend (лявото е stream)
//
// Member vs free:
//   member: лявото Е обектът (this)     →  v1 + v2  ок;  5 + v  НЕ (int няма +)
//   free:   и двата аргумента явни      →  5 + v  може, ако има converting ctor
//
#include <iostream>

class Counter {
    int n;
public:
    explicit Counter(int n = 0) : n(n) {}

    int get() const { return n; }

    // member binary +
    Counter operator+(const Counter& other) const {
        return Counter(n + other.n);   // нов обект; this не се променя
    }

    // member +=  (променя лявото, връща *this за a += b += c)
    Counter& operator+=(const Counter& other) {
        n += other.n;
        return *this;
    }

    // unary -  (member, 0 аргумента „отвън“)
    Counter operator-() const { return Counter(-n); }
};

int main() {
    Counter a(3), b(4);

    Counter c = a + b;          // operator+  → 7
    std::cout << c.get() << "\n";

    a += b;                     // a става 7
    std::cout << a.get() << "\n";

    Counter d = -b;             // unary -   → -4
    std::cout << d.get() << "\n";

    // Counter e = 1 + a;       // грешка: member + → лявото трябва Counter
}

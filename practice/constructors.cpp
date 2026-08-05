// ТЕМА 13 (част 1) — само КОНСТРУКТОРИ
//
// Проблем: след Box b; полето може да е боклук, ако го пълниш на ръка.
// Конструктор = специален метод, вика се АВТОМАТИЧНО при създаване, пълни обекта.
//
//   Box()              default          → Box a;
//   Box(int)           параметризиран   → Box b(5);
//   Box(const Box&)    copy             → Box c(b);   // НОВ обект; параметър = const Type&
//
// b2 = b1  → assignment (друг механизъм), НЕ copy ctor.
// Box bad(); → НЕ е обект (декларация на функция).
//
#include <iostream>

class Box {
    int i;
public:
    Box() : i(0) {}                       // default
    explicit Box(int x) : i(x) {}         // параметризиран
    Box(const Box& o) : i(o.i) {}         // copy (o е псевдоним на източника)

    int  get() const { return i; }
    void set(int x)  { i = x; }
};

int main() {
    Box a;          // default        → i = 0
    Box b(5);       // параметризиран → i = 5
    Box c(b);       // copy           → i = 5 (копие от b)

    c.set(9);
    std::cout << a.get() << " " << b.get() << " " << c.get() << "\n";
    // печата: 0 5 9
}

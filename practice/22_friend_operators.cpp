// ТЕМА 22 (част 2) — friend + оператори / streams (главната практика)
//
// Искаме:  cout << p;   и   if (a == b)
//
// Защо НЕ member за << ?
//   cout << p  → лявото е ostream, не Point.
//   Member би бил p.something(cout) — обърнат синтаксис.
//
// Защо friend?
//   свободна функция (правилен синтаксис) + private x,y
//   без public полета за целия свят.
//
// Type name;   = обект
// Type name(); = декларация на ФУНКЦИЯ (most vexing parse) — не обект!
//
#include <iostream>

class Point {
    int x, y;
public:
    Point(int x, int y) : x(x), y(y) {}

    friend std::ostream& operator<<(std::ostream& os, const Point& p);
    friend bool operator==(const Point& a, const Point& b);
};

std::ostream& operator<<(std::ostream& os, const Point& p) {
    return os << "(" << p.x << "," << p.y << ")";
}

bool operator==(const Point& a, const Point& b) {
    return a.x == b.x && a.y == b.y;
}

int main() {
    Point a(3, 4);
    Point b(3, 4);
    Point c(1, 2);

    std::cout << a << "\n";                 // (3,4)
    if (a == b) std::cout << "a == b\n";    // yes
    if (!(a == c)) std::cout << "a != c\n"; // yes
}

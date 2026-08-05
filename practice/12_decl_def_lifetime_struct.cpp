// ТЕМА 12: Декларация = „името съществува“; дефиниция = пълното тяло. Обектът се създава при
// дефиницията си и се унищожава в края на обхвата {}. struct ≈ class, default public vs private.
#include <iostream>

class Box;                    // декларация (forward) — само името

class Box {                   // дефиниция на типа
public:
    int w;
    void show();              // декларация на метод
};

void Box::show() {            // дефиниция на метод (извън класа)
    std::cout << w << "\n";
}

struct Point {                // struct: членовете са public по подразбиране
    int x, y;
};

int main() {
    Box b;                    // създаване (нужна е дефиницията на класа)
    b.w = 5;
    b.show();
    // тук b още живее
    {
        Point p;              // локален обект
        p.x = 1; p.y = 2;
        std::cout << p.x << " " << p.y << "\n";
    }                         // p се унищожава тук
}                             // b се унищожава тук

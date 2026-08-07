// ТЕМА 23 (част 2) — аритметични операции (практика: Vec2)
//
// Често:
//   + - * /     → връщат НОВ обект (const member или free)
//   += -= *= /= → променят *this, връщат Type&
//
// Добра практика: напиши += , после + чрез него (по-малко дублиране).
// Free + friend: симетрично; member: по-просто за начало.
//
#include <iostream>

class Vec2 {
    int x, y;
public:
    Vec2(int x = 0, int y = 0) : x(x), y(y) {}

    int getX() const { return x; }
    int getY() const { return y; }

    Vec2& operator+=(const Vec2& o) {
        x += o.x;
        y += o.y;
        return *this;
    }

    Vec2& operator-=(const Vec2& o) {
        x -= o.x;
        y -= o.y;
        return *this;
    }

    // скалар: v * 3
    Vec2& operator*=(int k) {
        x *= k;
        y *= k;
        return *this;
    }

    friend std::ostream& operator<<(std::ostream& os, const Vec2& v) {
        return os << "(" << v.x << "," << v.y << ")";
    }
};

// free +  (използва +=)
Vec2 operator+(Vec2 a, const Vec2& b) {   // a е копие
    a += b;
    return a;
}

Vec2 operator-(Vec2 a, const Vec2& b) {
    a -= b;
    return a;
}

Vec2 operator*(Vec2 v, int k) {
    v *= k;
    return v;
}

// симетрия: 3 * v  (member v*3 не стига — лявото е int)
Vec2 operator*(int k, Vec2 v) {
    v *= k;
    return v;
}

int main() {
    Vec2 a(1, 2), b(3, 4);

    std::cout << (a + b) << "\n";   // (4,6)
    std::cout << (b - a) << "\n";   // (2,2)
    std::cout << (a * 3) << "\n";   // (3,6)
    std::cout << (3 * a) << "\n";   // (3,6)  — free operator*(int, Vec2)

    a += b;
    std::cout << a << "\n";         // (4,6)
}

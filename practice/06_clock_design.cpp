// ТЕМА 6: Проектът се разбива на класове с ясна отговорност (Time=състояние/тик, Clock=сглобка).
// Диаграма на класове = типове и връзки (Clock ИМА Time); диаграма на обекти = конкретни инстанции.
// Елементи: private данни, public tick/print, composition — main е тънък оркестратор.
#include <iostream>
#include <iomanip>

class Time {  // един клас = една отговорност
private:
    int h = 0, m = 0, s = 0;
public:
    void set(int hh, int mm, int ss) { h = hh; m = mm; s = ss; }
    void tick() {                     // +1 сек + пренос
        if (++s == 60) { s = 0; if (++m == 60) { m = 0; h = (h + 1) % 24; } }
    }
    void print() const {
        std::cout << std::setfill('0') << std::setw(2) << h << ":"
                  << std::setw(2) << m << ":" << std::setw(2) << s << "\n";
    }
};

class Clock {                         // composition: Clock ИМА Time (не наследява)
private:
    Time t;
public:
    void set(int h, int m, int s) { t.set(h, m, s); }
    void tick() { t.tick(); }
    void show() const { t.print(); }
};

int main() {
    Clock c;                          // обект; c.t би било Time инстанция вътре
    c.set(23, 59, 58);
    c.show(); c.tick(); c.tick(); c.show();  // 23:59:58 -> 00:00:00
}

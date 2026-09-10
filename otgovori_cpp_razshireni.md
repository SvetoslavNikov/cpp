# C++ - разширени отговори за изпит

Само C++ и общо ООП. Заглавията не са променяни. Във всеки отговор влизат
думите от заглавието, а краткият код покрива всички части на въпроса.

## 1. Обекти и класове. Дефиниция на клас. Общи понятия и концепции.

Класът е потребителски тип, а обектът е конкретна негова инстанция със собствено
състояние. Дефиницията на клас описва данните и операциите върху тях на едно място.
Общите понятия и концепции на ООП са капсулация, наследяване, полиморфизъм и
абстракция: капсулацията скрива реализацията, а абстракцията показва само нужното
поведение.

```cpp
#include <iostream>
#include <string>

class User {                         // дефиниция на клас
private:
    std::string name;                // състояние на бъдещите обекти
public:
    User(std::string n) : name(std::move(n)) {}
    void hello() const { std::cout << "Hi, " << name << '\n'; }
};

int main() {
    User u("Ivan");                  // обект = инстанция на класа
    u.hello();
}
```

## 2. Методи и параметри. Даннови членове и пропъртита.

Методът е функция на класа и описва поведението на обектите. Параметрите подават
вход към метода. Данновите членове пазят състоянието в самия обект. В C++ няма
вградени пропъртита като в C#, затова getter и setter играят тази роля и позволяват
валидация при четене и запис.

```cpp
#include <iostream>

class Account {
private:
    double balance = 0;              // даннов член
public:
    double getBalance() const {      // пропърти за четене
        return balance;
    }
    void setBalance(double value) {  // метод с параметър; пропърти за запис
        if (value >= 0) balance = value;
    }
};

int main() {
    Account a;
    a.setBalance(50);
    std::cout << a.getBalance() << '\n';
}
```

## 3. Модификатори на достъп в клас.

Модификаторите на достъп в клас ограничават кой може да пипа членовете: `private`
само самият клас и неговите приятели, `protected` още и наследниците, `public` —
външният код. В `class` достъпът по подразбиране е `private`, а в `struct` е
`public`. Така се постига капсулация.

```cpp
#include <iostream>

class Base {
private:
    int hidden = 1;                  // само Base и friend
protected:
    int forKids = 2;                 // Base + наследници
public:
    int open = 3;                    // всички
    int getHidden() const { return hidden; }
};

class Child : public Base {
public:
    int sum() const { return forKids + open; }   // hidden тук е недостъпен
};

int main() {
    Child c;
    std::cout << c.open << " " << c.sum() << '\n';
}
```

## 4. Accessor-методи. Mutator-метод.

Accessor-методът (getter) връща данни от обекта и обикновено е `const`, за да не
го променя. Mutator-методът (setter) променя вътрешното състояние след проверка.
Заедно пазят инвариантите: възрастта не става отрицателна, балансът не се пипа
директно отвън.

```cpp
#include <iostream>

class Person {
private:
    int age = 0;
public:
    int getAge() const { return age; }           // accessor
    void setAge(int value) {                     // mutator
        if (value >= 0) age = value;
    }
};

int main() {
    Person p;
    p.setAge(20);
    std::cout << p.getAge() << '\n';
}
```

## 5. Методи на клас. Видове и модификатори. Припокриване.

Методите на клас биват обикновени, `const`, `static` и `virtual` — това са
основните видове и модификатори. `const` метод не променя логическото състояние,
`static` принадлежи на класа, не на обекта. Припокриването (overloading) е няколко
метода с едно име и различни параметри; компилаторът избира версията по
извикването. Това не е `override` на виртуална функция.

```cpp
#include <iostream>
#include <string>

class Printer {
public:
    void print(int x) const { std::cout << x << '\n'; }
    void print(const std::string& s) const {     // припокриване по параметър
        std::cout << s << '\n';
    }
    static void banner() { std::cout << "Printer\n"; }  // static метод
};

int main() {
    Printer::banner();
    Printer p;
    p.print(7);
    p.print("hi");
}
```

## 6. Програмни практики: цифров часовник - диаграми на класове и обекти.

При програмни практики цифровият часовник се разбива на класове с ясна
отговорност: `Time` пази часа и тика, `Clock` го сглобява. Диаграмата на класове
показва типовете и връзката has-a (`Clock` съдържа `Time`). Диаграмата на обекти
показва конкретни инстанции в даден момент, например един `Clock` с вложен
`Time{23,59,58}`.

```cpp
#include <iostream>
#include <iomanip>

class Time {                                     // клас в диаграмата
    int h = 0, m = 0, s = 0;
public:
    void set(int hh, int mm, int ss) { h = hh; m = mm; s = ss; }
    void tick() {
        if (++s == 60) { s = 0; if (++m == 60) { m = 0; h = (h + 1) % 24; } }
    }
    void print() const {
        std::cout << std::setfill('0') << std::setw(2) << h << ':'
                  << std::setw(2) << m << ':' << std::setw(2) << s << '\n';
    }
};

class Clock {                                    // Clock ИМА Time
    Time t;
public:
    void set(int h, int m, int s) { t.set(h, m, s); }
    void tick() { t.tick(); }
    void show() const { t.print(); }
};

int main() {
    Clock c;                                     // обект в обектната диаграма
    c.set(23, 59, 58);
    c.tick();
    c.tick();
    c.show();                                    // 00:00:00
}
```

## 7. Групиране на обекти. Колекции и итератори.

Групирането на обекти означава един обект да държи много други. Колекции като
`std::vector` пазят елементите, а итераторите дават общ начин за обхождане без да
зависим от вътрешната структура: `begin()` е първият, `end()` е след последния.
`Notebook` групира много `Note` в една колекция.

```cpp
#include <iostream>
#include <string>
#include <vector>

class Note {
    std::string title, body;
public:
    Note(const std::string& t, const std::string& b) : title(t), body(b) {}
    void print() const { std::cout << "[" << title << "] " << body << '\n'; }
};

class Notebook {
    std::vector<Note> notes;                     // колекция = групиране
public:
    void add(const Note& n) { notes.push_back(n); }
    void printAll() const {
        for (auto it = notes.begin(); it != notes.end(); ++it)  // итератор
            it->print();
    }
};

int main() {
    Notebook nb;
    nb.add(Note("T7", "vector"));
    nb.printAll();
}
```

## 8. Проектиране на класова йерархия в обектно-структурирана програма.

Проектирането на класова йерархия в обектно-структурирана програма слага общото
в базов клас, а специалното — в производни. Наследяване се ползва само при истинска
връзка is-a, не за повторна употреба на код. Така полиморфизмът работи през базовия
тип, а дублирането намалява.

```cpp
#include <iostream>

class Vehicle {                                  // общото в йерархията
protected:
    int wheels;
public:
    explicit Vehicle(int w) : wheels(w) {}
    virtual ~Vehicle() = default;
    int getWheels() const { return wheels; }
};

class Car : public Vehicle {                     // Car Е Vehicle
public:
    explicit Car(int w) : Vehicle(w) {}
    void openTrunk() const { std::cout << "trunk\n"; }
};

int main() {
    Car c(4);                                    // обект в програмата
    std::cout << c.getWheels() << '\n';
    c.openTrunk();
}
```

## 9. Оценка на качеството на кода. Свързаност и структурираност.

Оценката на качеството на кода гледа четимост, тестове и лесна промяна. Ниска
свързаност (coupling) означава класовете да зависят малко един от друг. Добра
структурираност (висока кохезия) означава един клас да държи логически свързани
отговорности. Тогава промяната остава локална.

```cpp
#include <iostream>
#include <string>

class Logger {                                   // висока кохезия: само лог
public:
    void info(const std::string& msg) const { std::cout << msg << '\n'; }
};

class Order {                                    // ниска свързаност: ползва Logger,
    Logger& log;                                 // без да знае как печата
public:
    explicit Order(Logger& l) : log(l) {}
    void confirm() { log.info("order ok"); }
};

int main() {
    Logger log;
    Order o(log);
    o.confirm();
}
```

## 10. Качество на код: дублиращи се фрагменти. Целево-ориентиран проект.

Качеството на код пада при дублиращи се фрагменти: една и съща логика се поправя
на няколко места и лесно се разминава. В целево-ориентиран проект общото се вади
във функция или клас според целта на програмата, а не се маха всяко повторение на
всяка цена. Дублира се текст, не се дублира бизнес правило.

```cpp
#include <iostream>
#include <vector>

int sum(const std::vector<int>& v) {             // общ фрагмент, една цел
    int s = 0;
    for (int x : v) s += x;
    return s;
}

int main() {
    std::vector<int> a{1, 2, 3};
    std::vector<int> b{4, 5};
    std::cout << sum(a) + sum(b) << '\n';        // без копи-пейст на цикъла
}
```

## 11. Проектиране на обектно-структуриран код.

Проектирането на обектно-структуриран код започва с обектите, техните
отговорности и взаимодействия. Всеки клас има една ясна роля и малък публичен
интерфейс; детайлите се скриват. Композицията често е по-гъвкава от наследяването:
`Cart` има `Item`-и, а не е `Item`.

```cpp
#include <iostream>
#include <string>
#include <vector>

class Item {
    std::string name;
public:
    explicit Item(std::string n) : name(std::move(n)) {}
    const std::string& getName() const { return name; }
};

class Cart {                                     // композиция, не йерархия
    std::vector<Item> items;
public:
    void add(Item item) { items.push_back(std::move(item)); }
    void list() const {
        for (const Item& i : items) std::cout << i.getName() << '\n';
    }
};

int main() {
    Cart cart;
    cart.add(Item("book"));
    cart.list();
}
```

## 12. Класове и обекти: разделяне на декларация и дефиниция. Създаване и унищожаване на обекти.

При класове и обекти разделянето на декларация и дефиниция слага интерфейса в
`.h`, а телата на методите в `.cpp`. Създаването на обект вика конструктора;
унищожаването му вика деструктора автоматично в края на живота (край на блока
или `delete`). Така компилационните зависимости остават малки.

```cpp
// User.h — декларация
class User {
public:
    explicit User(const char* name);
    ~User();
    void hello() const;
private:
    const char* name;
};

// User.cpp — дефиниция
#include <iostream>
User::User(const char* name) : name(name) { std::cout << "create\n"; }
User::~User() { std::cout << "destroy\n"; }
void User::hello() const { std::cout << name << '\n'; }

// main.cpp — създаване и унищожаване
int main() {
    User u("Ivan");                              // създаване
    u.hello();
}                                                // унищожаване на u
```

## 13. Конструктори и деструктори. Видове конструктори.

Конструкторът инициализира обекта, деструкторът освобождава ресурсите му. Видове
конструктори в C++ са default, параметризиран, copy и move. Конструктор не може да
е `virtual` или `static`; при полиморфен базов клас деструкторът обикновено е
`virtual`. Copy прави дълбоко копие, move прехвърля ресурса.

```cpp
#include <iostream>
#include <utility>

class Array {
    int* data;
    int size;
public:
    Array() : data(nullptr), size(0) {}                          // default
    explicit Array(int n) : data(new int[n]), size(n) {}         // параметризиран
    Array(const Array& o) : data(new int[o.size]), size(o.size) { // copy
        for (int i = 0; i < size; ++i) data[i] = o.data[i];
    }
    Array(Array&& o) noexcept : data(o.data), size(o.size) {     // move
        o.data = nullptr;
        o.size = 0;
    }
    ~Array() { delete[] data; }                                  // деструктор
};

int main() {
    Array a(3);
    Array b = a;                                                 // copy
    Array c = std::move(a);                                      // move
}
```

## 14. Дефиниране на връзки. Взаимодействия на обекти по вертикала и хоризонтала.

Дефинирането на връзки описва как обектите се познават. Взаимодействията на
обекти по вертикала са is-a — наследяване между базов и производен клас. По
хоризонтала са association, aggregation и composition: обект ползва или съдържа
друг, без да му е подтип. Комуникацията минава през публични методи.

```cpp
#include <iostream>
#include <string>

class Engine {                                   // част за composition
    int hp;
public:
    explicit Engine(int h) : hp(h) {}
    int getHp() const { return hp; }
};

class Car {                                      // хоризонтално: Car ИМА Engine
    Engine eng;
public:
    explicit Car(int hp) : eng(hp) {}
    void info() const { std::cout << eng.getHp() << "hp\n"; }
};

class Vehicle {                                  // вертикално: is-a база
public:
    virtual ~Vehicle() = default;
};
class Bike : public Vehicle {};                  // Bike Е Vehicle

int main() {
    Car c(150);
    c.info();
    Bike b;
    Vehicle& v = b;                              // вертикално взаимодействие
    (void)v;
}
```

## 15. Подтипове, подкласове и присвоявания. Предаване на параметри.

Подкласът наследява базов клас. Той е и подтип, ако спазва договора на базата и
може да се ползва там, където се очаква базовият тип. При присвоявания по стойност
от производен към базов обект се реже object slicing. При предаване на параметри
за полиморфизъм се ползва указател или референция към базата, не копие.

```cpp
#include <iostream>

class Animal {
public:
    virtual void sound() const { std::cout << "?\n"; }
    virtual ~Animal() = default;
};
class Dog : public Animal {                      // подклас и подтип
public:
    void sound() const override { std::cout << "woof\n"; }
};

void speak(const Animal& a) {                    // параметър: референция
    a.sound();
}

int main() {
    Dog d;
    Animal& r = d;                               // присвояване на референция — без slicing
    r.sound();                                   // woof
    speak(d);                                    // подтип като параметър

    Animal sliced = d;                           // присвояване по стойност — slicing
    sliced.sound();                              // Animal::sound
}
```

## 16. Наследяемост. Полиморфизъм. Достъп до методи и данни.

Наследяемостта позволява производният клас да използва и разширява базовия.
Полиморфизмът прави една и съща операция да има различна реализация според
действителния тип. Достъпът до методи и данни зависи от `public`/`protected`/
`private` и от вида наследяване: при `public` наследяване публичното на базата
остава публично за клиента.

```cpp
#include <iostream>

class Animal {
protected:
    int age = 1;                                 // данни за наследниците
public:
    virtual void sound() const { std::cout << "?\n"; }
    virtual ~Animal() = default;
};

class Dog : public Animal {                      // наследяемост
public:
    void sound() const override { std::cout << "woof " << age << '\n'; }
};

int main() {
    Dog d;
    Animal& a = d;
    a.sound();                                   // полиморфизъм → Dog::sound
}
```

## 17. Виртуализация и реализация на полиморфизма. Абстрактни класове и виртуални функции.

Виртуализацията е механизмът (vtable), чрез който се прави реализацията на
полиморфизма: при викане през базова референция се избира методът на истинския
тип. Абстрактните класове имат поне една pure virtual функция и не се
инстанцират. Виртуалните функции се предефинират с `override`; базовата версия
се вика изрично с `Base::method()`.

```cpp
#include <iostream>

class Shape {                                    // абстрактен клас
public:
    virtual double area() const = 0;             // виртуална / pure virtual
    virtual ~Shape() = default;
};

class Square : public Shape {
    double side;
public:
    explicit Square(double s) : side(s) {}
    double area() const override { return side * side; }
};

class NamedSquare : public Square {
public:
    using Square::Square;
    double area() const override {
        std::cout << "named ";
        return Square::area();                   // виртуална на базов клас
    }
};

int main() {
    NamedSquare s(2);
    Shape& sh = s;                               // полиморфизъм през база
    std::cout << sh.area() << '\n';              // named 4
}
```

## 18. Вграждане на обекти. Copy-конструктори. Присвоявания и обекти.

Вграждането на обекти е композиция: член-обект се създава заедно със съдържащия
клас. Copy-конструкторът прави нов обект от съществуващ. Присвояванията променят
вече създаден обект чрез `operator=`. При класове с ресурс се спазват Rule of 3/5
или Rule of 0, за да не споделят два обекта една и съща памет.

```cpp
#include <iostream>
#include <string>

class Engine {
    int hp;
public:
    explicit Engine(int h) : hp(h) {}
    Engine(const Engine& o) : hp(o.hp) { std::cout << "Engine copy\n"; }
};

class Car {
    Engine engine;                               // вграждане
    std::string model;
public:
    Car(std::string m, int hp) : engine(hp), model(std::move(m)) {}
    Car(const Car& o) : engine(o.engine), model(o.model) {}   // copy-конструктор
    Car& operator=(const Car& o) {               // присвояване
        if (this != &o) {
            engine = o.engine;
            model = o.model;
        }
        return *this;
    }
};

int main() {
    Car a("Golf", 150);
    Car b = a;                                   // copy
    Car c("Polo", 90);
    c = a;                                       // присвояване на обекти
}
```

## 19. Референтни параметри. Работа с референции. Връщане на референции.

Референтните параметри позволяват на функцията да работи директно със съществуващ
обект, без да създава негово копие. При работа с референции `T&` позволява промяна
на оригиналния обект, а `const T&` дава достъп само за четене и е подходящо за
подаване на големи обекти. Връщане на референции е безопасно само когато върнатата
референция сочи към обект, който ще съществува и след приключване на функцията.
Не трябва да се връща референция към локална променлива, защото тя се унищожава
при излизане от функцията.

```cpp
#include <iostream>
#include <string>

void increment(int& value) {
    ++value; // Променя оригиналната променлива.
}

void print(const std::string& text) {
    std::cout << text << '\n'; // Само чете текста без копиране.
}

int& greater(int& first, int& second) {
    return first > second ? first : second;
}

int main() {
    int a = 3;
    int b = 8;

    increment(a);
    print("a = " + std::to_string(a));

    greater(a, b) = 10; // Променя по-голямата от двете променливи.
}
```

## 20. Конструиране на вградени обекти. Деструкция на вградени обекти.

Конструирането на вградени обекти става преди тялото на конструктора на
съдържащия клас, чрез member initializer list и по реда на декларация в класа, не
по реда в списъка. Деструкцията на вградени обекти е в обратен ред, след тялото на
деструктора на обвивката. Член, който няма default конструктор, трябва да се
инициализира изрично.

```cpp
#include <iostream>

class Engine {
public:
    explicit Engine(int hp) { std::cout << "Engine " << hp << '\n'; }
    ~Engine() { std::cout << "~Engine\n"; }
};

class Car {
    Engine engine;                               // вграден обект
public:
    Car() : engine(100) { std::cout << "Car\n"; } // първо Engine, после Car
    ~Car() { std::cout << "~Car\n"; }             // първо ~Car, после ~Engine
};

int main() {
    Car c;
}                                                // ~Car, после ~Engine
```

## 21. Заделяне на обекти от динамичната памет.

Заделянето на обекти от динамичната памет става с `new` и се освобождава с
`delete`. Ако указателят се загуби, има leak; ако се `delete` два пъти или се ползва
след това — undefined behavior. Проблемът често е неясно кой обект притежава
другия. Модерният C++ ползва RAII: `unique_ptr` освобождава автоматично.

```cpp
#include <iostream>
#include <memory>
#include <string>

class User {
    std::string name;
public:
    explicit User(std::string n) : name(std::move(n)) {}
    void hello() const { std::cout << name << '\n'; }
};

int main() {
    User* raw = new User("Ivan");                // ръчно заделяне
    raw->hello();
    delete raw;                                  // ръчно освобождаване

    auto p = std::make_unique<User>("Maria");    // RAII, без delete
    p->hello();
}
```

## 22. Приятелски класове и приятелски функции. Статични членове на клас.

Приятелският клас и приятелската функция виждат `private`/`protected` членове,
без да са обикновени методи на класа. Това е силна връзка и се ползва рядко —
типично за `operator<<`. Статичните членове на клас са общи за всички обекти:
една `count` за целия тип, дефинирана извън класа.

```cpp
#include <iostream>

class Counter {
    int value = 0;
    static int total;                            // статичен член
    friend void show(const Counter& c);          // приятелска функция
    friend class Inspector;                      // приятелски клас
public:
    Counter() { ++total; }
    static int getTotal() { return total; }
};

int Counter::total = 0;

void show(const Counter& c) { std::cout << c.value << '\n'; }

class Inspector {
public:
    int peek(const Counter& c) const { return c.value; }
};

int main() {
    Counter a, b;
    show(a);
    std::cout << Counter::getTotal() << '\n';    // 2
}
```

## 23. Припокриване на оператори. Същност, ограничения.

Същността на припокриването на оператори е `a + b` да значи `a.operator+(b)`
(или свободна `operator+(a, b)`) за потребителски тип. Ограниченията: не се
измислят нови символи, не се сменят приоритет, асоциативност и брой операнди;
`::`, `.`, `.*`, `?:` не се припокриват; `=`, `[]`, `()`, `->` трябва да са членове.
Операторът трябва да пази естествения си смисъл.

```cpp
#include <iostream>

struct Point {
    int x, y;
    Point operator+(const Point& o) const {      // припокриване на +
        return {x + o.x, y + o.y};
    }
};

int main() {
    Point a{1, 2}, b{3, 4};
    Point c = a + b;                             // (4, 6)
    std::cout << c.x << ' ' << c.y << '\n';
}
```

## 24. Преобразувания и операции-преобразувания.

Преобразуванията биват неявни и явни (`static_cast`, `dynamic_cast`, `const_cast`,
`reinterpret_cast`). Операциите-преобразувания са conversion operator-и:
`operator T()`, които обръщат обекта към друг тип. Обратната посока е converting
constructor. `explicit` спира тихото неявно преобразуване.

```cpp
#include <iostream>

class Meter {
    int m;
public:
    explicit Meter(int v) : m(v) {}              // converting ctor, но explicit
    explicit operator int() const { return m; }  // операция-преобразуване
};

int main() {
    double d = 3.7;
    int x = static_cast<int>(d);                 // явно преобразуване

    Meter m(5);
    int n = static_cast<int>(m);                 // вика operator int()
    std::cout << x << ' ' << n << '\n';
}
```

## 25. CASE: обектно-структурирана програмна система - плащане.

CASE тук е учебен случай: обектно-структурирана програмна система за плащане с
обща абстракция `Payment` и конкретни `CardPayment` / `BankPayment`. UML на
класовете би показал базов интерфейс, наследници, методи `pay` и връзка is-a.
Клиентът работи полиморфно през `Payment*`, без да знае конкретния тип.

```cpp
#include <iostream>

class Payment {                                  // абстракция в системата
public:
    virtual void pay(double amount) = 0;
    virtual ~Payment() = default;
};

class CardPayment : public Payment {
public:
    void pay(double amount) override {
        std::cout << "card " << amount << '\n';
    }
};

class BankPayment : public Payment {
public:
    void pay(double amount) override {
        std::cout << "bank " << amount << '\n';
    }
};

void checkout(Payment& p, double amount) {       // полиморфно плащане
    p.pay(amount);
}

int main() {
    CardPayment card;
    checkout(card, 20);
}
```

## 26. Разширяване функционалността на системата за плащания: интерфейси.

Разширяването на функционалността на системата за плащания става чрез интерфейси:
в C++ това е абстрактен клас с pure virtual функции и виртуален деструктор.
Нов начин на плащане наследява интерфейса и го реализира; кодът през `Payment&`
не се пипа. Това е Open/Closed върху вече наличната система.

```cpp
#include <iostream>

class Payment {                                  // интерфейс
public:
    virtual void pay(double amount) = 0;
    virtual ~Payment() = default;
};

class CryptoPayment : public Payment {           // ново плащане, без промяна на checkout
public:
    void pay(double amount) override {
        std::cout << "crypto " << amount << '\n';
    }
};

void checkout(Payment& p, double amount) { p.pay(amount); }

int main() {
    CryptoPayment c;
    checkout(c, 15);
}
```

## 28. Софтуерни контракти. Пред- и пост-условия. Инварианти.

Софтуерният контракт е договор между викащия и метода. Пред-условието трябва да
е вярно преди извикването (например `amount > 0`). Пост-условието е гарантирано
след успех (балансът е намален с `amount`). Инвариантът важи за обекта през целия
му живот (балансът никога не е отрицателен). Нарушението е грешка на клиента или
на реализацията.

```cpp
#include <iostream>
#include <stdexcept>

class Account {
    double balance = 100;                        // инвариант: balance >= 0
public:
    double withdraw(double amount) {
        // пред-условие: amount > 0 && amount <= balance
        if (amount <= 0 || amount > balance)
            throw std::invalid_argument("bad amount");
        balance -= amount;
        // пост-условие: новото balance е старото минус amount
        return balance;
    }
};

int main() {
    Account a;
    std::cout << a.withdraw(40) << '\n';         // 60
}
```

## 30. Контракт и наследяване. Ограничаване на областта в дъщерен обект.

При контракт и наследяване дъщерният обект трябва да може да замести базовия:
не засилва пред-условията и не отслабва пост-условията. Ограничаването на
областта в дъщерен обект — например базовият `withdraw` приема всяка положителна
сума, а наследникът приема само до 50 — чупи полиморфния клиент, който спазва
само договора на базата.

```cpp
#include <iostream>
#include <stdexcept>

class Account {
public:
    virtual void withdraw(double amount) {       // контракт: amount > 0
        if (amount <= 0) throw std::invalid_argument("amount");
        std::cout << "withdraw " << amount << '\n';
    }
    virtual ~Account() = default;
};

class LimitedAccount : public Account {
public:
    void withdraw(double amount) override {
        if (amount > 50)                         // по-тясна област — нарушение
            throw std::invalid_argument("too big");
        Account::withdraw(amount);
    }
};

void take(Account& a) { a.withdraw(80); }        // валидно за базата, не за Limited

int main() {
    Account a;
    take(a);                                     // ок
    // LimitedAccount l; take(l);                // чупи договора на базата
}
```

## 31. Обектен дизайн: SOLID, Open/Closed и Single Responsibility.

Обектният дизайн по SOLID държи модулите независими. Open/Closed: класът е
отворен за разширяване (нов наследник) и затворен за ненужна промяна на
съществуващия код. Single Responsibility: един клас — една причина за промяна.
`Shape` се рисува сам; `Drawer` не се редактира при нова фигура.

```cpp
#include <iostream>

class Shape {                                    // OCP: нови фигури чрез наследяване
public:
    virtual void draw() const = 0;
    virtual ~Shape() = default;
};

class Circle : public Shape {
public:
    void draw() const override { std::cout << "circle\n"; }
};

class Drawer {                                   // SRP: само обхожда и вика draw
public:
    void show(const Shape& s) const { s.draw(); }
};

int main() {
    Circle c;
    Drawer d;
    d.show(c);
}
```

## 32. Обектен дизайн: принцип на верижната отговорност.

В обектния дизайн принципът на верижната отговорност (Chain of Responsibility)
нарежда обработчици един след друг. Всеки решава дали да обработи заявката, или
да я подаде нататък. Изпращачът не познава конкретния получател; веригата се
удължава без да се пипа клиентът.

```cpp
#include <iostream>

class Handler {
    Handler* next = nullptr;
public:
    Handler* setNext(Handler* n) { next = n; return n; }
    virtual void handle(int request) {
        if (next) next->handle(request);
    }
    virtual ~Handler() = default;
};

class SmallHandler : public Handler {
public:
    void handle(int request) override {
        if (request < 10) std::cout << "small " << request << '\n';
        else Handler::handle(request);
    }
};

class BigHandler : public Handler {
public:
    void handle(int request) override {
        std::cout << "big " << request << '\n';
    }
};

int main() {
    SmallHandler small;
    BigHandler big;
    small.setNext(&big);
    small.handle(3);                             // small
    small.handle(20);                            // big
}
```

## 33. Обектен дизайн: double dispatch в run-time.

В обектния дизайн double dispatch в run-time избира операцията според
динамичния тип на два обекта, не само на един. В C++ няма вграден механизъм: прави
се с две виртуални викания, обикновено Visitor. Първо `accept` на фигурата, после
`visit` на посетителя — и двете се резолвират по истинския тип.

```cpp
#include <iostream>

class Circle;
class Rect;

class Visitor {
public:
    virtual void visit(Circle& c) = 0;
    virtual void visit(Rect& r) = 0;
    virtual ~Visitor() = default;
};

class Shape {
public:
    virtual void accept(Visitor& v) = 0;
    virtual ~Shape() = default;
};

class Circle : public Shape {
public:
    void accept(Visitor& v) override { v.visit(*this); }
};
class Rect : public Shape {
public:
    void accept(Visitor& v) override { v.visit(*this); }
};

class Draw : public Visitor {
public:
    void visit(Circle&) override { std::cout << "draw circle\n"; }
    void visit(Rect&) override { std::cout << "draw rect\n"; }
};

int main() {
    Circle c;
    Draw d;
    Shape& s = c;
    s.accept(d);                                 // run-time: Circle + Draw
}
```

## 37. Lambda изрази. Функции-обекти и функции през указатели.

Lambda изразът е анонимна функция на мястото на употреба. Функциите-обекти
(functors) са класове с `operator()` и могат да имат състояние. Функциите през
указатели са само адрес на свободна функция, без capture. Ламбдата е по-кратък
functor и е удобна за STL алгоритми.

```cpp
#include <algorithm>
#include <iostream>
#include <vector>

int add(int a, int b) { return a + b; }

struct Times {                                   // функция-обект
    int k;
    int operator()(int x) const { return x * k; }
};

int main() {
    int (*fp)(int, int) = add;                   // указател към функция
    std::cout << fp(2, 3) << '\n';

    Times t{10};
    std::cout << t(3) << '\n';

    std::vector<int> v{3, 1, 2};
    std::sort(v.begin(), v.end(),
              [](int a, int b) { return a < b; });  // lambda израз
    std::cout << v[0] << '\n';
}
```

## 38. Синтактични елементи на lambda изразите в C++.

Синтактичните елементи на lambda изразите в C++ са
`[capture](params) mutable -> ret { body }`. `[=]` копира използваните променливи,
`[&]` ги прихваща по референция, `[x]` / `[&x]` — конкретно. Типът на връщане често
се извежда. `mutable` позволява промяна на копирания capture.

```cpp
#include <iostream>

int main() {
    int n = 10;
    auto add = [n](int x) -> int {               // capture, params, return type, body
        return x + n;
    };
    auto addRef = [&n](int x) { return x + n; };
    n = 20;
    std::cout << add(5) << '\n';                 // 15 — старото копие
    std::cout << addRef(5) << '\n';              // 25 — през референция
}
```

## 39. Lambda изрази в асинхронни изчисления. Определяне на типа.

Lambda изразите в асинхронни изчисления се подават директно на `std::async` или
`std::thread`. Определянето на типа на ламбда е уникален unnamed closure; пише се
`auto` или се прибира в `std::function`. Capture по референция е опасен, ако
обектът умре преди задачата да свърши.

```cpp
#include <future>
#include <iostream>

int main() {
    auto task = [] { return 40 + 2; };           // типът е уникален closure
    auto future = std::async(std::launch::async, task);  // асинхронно
    std::cout << future.get() << '\n';           // 42
}
```

## 40. Стандартизирани средства в C++ за паралелизация.

Стандартизираните средства в C++ за паралелизация са `std::thread`, `std::async`,
`std::future` и синхронизационни примитиви. Нишката трябва да се `join` (или
`detach`); иначе деструкторът вика `std::terminate`. `std::async` връща `future`,
от който се взима резултатът. `std::thread` е move-only: собствеността се
прехвърля с `std::move`.

```cpp
#include <future>
#include <iostream>
#include <thread>

int main() {
    std::thread t([] { std::cout << "thread\n"; });
    t.join();

    std::thread a([] {});
    std::thread b = std::move(a);                // собственост на нишката
    b.join();

    std::future<int> f = std::async(std::launch::async, [] { return 42; });
    std::cout << f.get() << '\n';
}
```

## 41. Синхронизация при паралелни изчисления. Атомарни типове.

Синхронизацията при паралелни изчисления гарантира, че няколко нишки могат да
четат и пишат общо състояние без data race. Без нея едновременният достъп до една
и съща променлива дава неопределен резултат. Атомарните типове като `std::atomic<T>`
правят операциите върху стойността неделими: четене, промяна и запис се изпълняват
като една стъпка. За прост брояч това стига и без mutex.

```cpp
#include <atomic>
#include <iostream>
#include <thread>
#include <vector>

std::atomic<int> counter{0};

void increment() {
    for (int i = 0; i < 1000; ++i) {
        counter.fetch_add(1);                    // атомарна операция
    }
}

int main() {
    std::vector<std::thread> threads;
    for (int i = 0; i < 4; ++i) {
        threads.emplace_back(increment);         // паралелни изчисления
    }
    for (auto& t : threads) t.join();
    std::cout << counter.load() << '\n';         // винаги 4000
}
```

## 42. Взаимни изключвания при паралелни изчисления и примитиви.

Взаимните изключвания при паралелни изчисления гарантират, че само една нишка е
в критичната секция. Примитивите са `std::mutex`, а RAII обвивките `std::lock_guard`
и `std::unique_lock` заключват в конструктора и отключват в деструктора. Mutex се
ползва, когато няколко стъпки трябва да са атомарни заедно, не само едно `++`.

```cpp
#include <iostream>
#include <mutex>
#include <thread>

int counter = 0;
std::mutex m;                                    // примитив за взаимно изключване

void work() {
    for (int i = 0; i < 100000; ++i) {
        std::lock_guard<std::mutex> lock(m);
        ++counter;                               // критична секция
    }
}

int main() {
    std::thread t1(work), t2(work);
    t1.join();
    t2.join();
    std::cout << counter << '\n';                // 200000
}
```

## 43. Условни променливи при паралелни изчисления.

Условните променливи при паралелни изчисления позволяват нишка да чака условие,
без да върти празен цикъл. `std::condition_variable` работи с `std::unique_lock`:
`wait` отключва mutex-а докато спи и го заключва отново при събуждане. Производителят
сменя данните под lock и вика `notify_one()` / `notify_all()`. Винаги се чака с
предикат срещу случайно събуждане.

```cpp
#include <condition_variable>
#include <iostream>
#include <mutex>
#include <thread>

std::mutex m;
std::condition_variable cv;
bool ready = false;
int data = 0;

void consumer() {
    std::unique_lock<std::mutex> lock(m);
    cv.wait(lock, [] { return ready; });
    std::cout << data << '\n';
}

void producer() {
    {
        std::lock_guard<std::mutex> lock(m);
        data = 42;
        ready = true;
    }
    cv.notify_one();
}

int main() {
    std::thread c(consumer), p(producer);
    c.join();
    p.join();
}
```

## 48. Обекти в паметта - особености и програмни грешки.

Особеностите на обектите в паметта зависят от живота: автоматичен (стек, край на
блока), динамичен (heap, до `delete`) или статичен. Типични програмни грешки са
out-of-bounds, dangling pointer, use-after-free, неинициализиран указател и leak.
RAII, контейнери и smart pointers намаляват тези грешки.

```cpp
#include <iostream>
#include <memory>
#include <vector>

int main() {
    int stack = 1;                               // автоматичен обект
    auto heap = std::make_unique<int>(2);        // динамичен, безопасен живот

    std::vector<int> v{1, 2, 3};
    std::cout << stack << ' ' << *heap << ' ' << v[0] << '\n';

    // int* p = new int(3); delete p; std::cout << *p;  // use-after-free
    // int a[2] = {0}; a[2] = 1;                        // out-of-bounds
}
```

## 49. Управление на памет в Linux системи: служебни структури.

Управлението на памет в Linux системи дели адресното пространство на text, data,
heap и stack. Върху heap allocator-ът (ptmalloc/glibc) реже блокове (chunks).
Служебните структури на свободния chunk са `prev_size`, `size` и указателите
`fd`/`bk` към съседите в двусвързания списък на bin-а. Макросът `unlink()` вади
chunk от този списък при сливане на съседни свободни блокове:
`FD->bk = BK; BK->fd = FD`. Повреда на `fd`/`bk` дава произволен запис в паметта.

```cpp
// Схема на свободен heap chunk (не е стандартен C++ API):
//   prev_size | size | fd | bk | потребителски данни...
//
// unlink(P):
//   FD = P->fd;
//   BK = P->bk;
//   FD->bk = BK;     // запис през служебните указатели
//   BK->fd = FD;

#include <cstdlib>
#include <iostream>

int main() {
    void* p = std::malloc(32);                   // блок от heap в Linux
    std::free(p);                                // връщане в bin; може да unlink-не съсед
    std::cout << "ok\n";
}
```

## 50. Препълване на буфер. Поглед отвътре.

Препълването на буфер е запис на повече байтове, отколкото масивът събира. Поглед
отвътре: локалните променливи и адресът за връщане стоят един до друг на стека;
байтове след края на `buffer` презаписват съседа или контролните данни. Класически
вход през `strcpy` без проверка. Защити: stack canary, NX/DEP, ASLR; в C++ —
`std::string` и проверка на дължина, не ръчен `char[]`.

```cpp
#include <cstring>
#include <iostream>

void unsafe(const char* input) {
    char buffer[8];
    // strcpy(buffer, input);                    // препълване, ако input е по-дълъг от 7
    std::strncpy(buffer, input, sizeof(buffer) - 1);
    buffer[sizeof(buffer) - 1] = '\0';
    std::cout << buffer << '\n';
}

int main() {
    unsafe("hi");
}
```

## 51. Атака от тип „frontlink“.

Атаката от тип „frontlink“ цели вмъкването на свободен chunk в двусвързания
списък на bin-а (операцията frontlink в dlmalloc/ptmalloc, обратното на unlink).
При вмъкване allocator-ът прави `P->fd = bin; P->bk = last; last->fd = P; bin->bk = P`.
Ако чрез препълване на предишен блок атакуващият подмени `bk` на свободния chunk,
`last->fd = P` записва адреса на P на избрано място (указател към функция, запис
в GOT и подобни). После това място се ползва като код/указател. Съвременният glibc
има проверки на `fd`/`bk` и затруднява атаката; идеята за изпита е фалшивите
служебни указатели при линкване.

```cpp
// frontlink(P) схематично:
//   FD = bin;
//   BK = bin->bk;          // "last"
//   P->bk = BK;
//   P->fd = FD;
//   BK->fd = P;            // произволен запис, ако BK е фалшив
//   FD->bk = P;
//
// Атаката: overflow в header на свободен chunk → фалшив bk → запис на &chunk
// върху избрано поле. Не е нужен работещ експлойт за отговора на изпита.

#include <cstdlib>
#include <iostream>

int main() {
    void* a = std::malloc(64);
    void* b = std::malloc(64);
    std::free(a);                                // a влиза в bin чрез frontlink
    std::free(b);
    std::cout << "two frees, chunks linked in bin\n";
}
```

## 52. Double-free vulnerabilities.

Double-free vulnerabilities възникват, когато един и същ динамичен блок се
освободи два пъти. Вторият `free` пипа вече невалиден chunk: allocator-ът може да
разбърка `fd`/`bk`, да върне един блок на два указателя или да падне. Това е
undefined behavior. Защита: една собственост — `unique_ptr` или нулиране след
`delete`, никога двама „собственици“ с ръчен `delete`.

```cpp
#include <iostream>
#include <memory>

int main() {
    int* p = new int(5);
    delete p;
    // delete p;                                 // double-free — забранено

    auto u = std::make_unique<int>(5);           // освобождава се точно веднъж
    std::cout << *u << '\n';
}
```

## 53. Динамично управление на памет в Windows.

Динамичното управление на памет в Windows минава през виртуална памет и heap на
процеса. Приложението вика `HeapAlloc` / `HeapFree` (или CRT `malloc` върху тях),
а ядрото дава страници с `VirtualAlloc`. C++ `new`/`delete` седят отгоре. За
обикновен код се предпочитат контейнери и smart pointers, не директният WinAPI.

```cpp
#include <iostream>
#include <memory>

int main() {
    // На Windows: new → CRT → HeapAlloc върху default heap на процеса.
    auto p = std::make_unique<int[]>(16);
    p[0] = 1;
    std::cout << p[0] << '\n';
}
```

## 54. Служебни структури в динамичния мениджмънт на паметта в Windows.

Служебните структури в динамичния мениджмънт на паметта в Windows са метаданните
на heap manager-а: заглавки на блокове (размер, флакове busy/free), списъци на
свободни chunk-ове с forward/back указатели, сегменти и (в по-стари версии)
lookaside / LFH. Повреда на тези полета чрез overflow, use-after-free или
double-free обърква allocator-а по същата идея като `fd`/`bk` в Linux.

```cpp
// Windows heap блок (схема):
//   header (size, flags) | user data | optional trailer
// Свободен блок: flink / blink към други свободни, като fd/bk в glibc.
// Lookaside/LFH държат малки блокове в бързи списъци по размер.

#include <iostream>
#include <vector>

int main() {
    std::vector<int> v(8);                       // CRT heap, със служебна заглавка преди v[0]
    v[0] = 42;
    std::cout << v[0] << '\n';
}
```

## 55. Препълване на буфер в Windows и атаки, базирани на това.

Препълването на буфер в Windows е същият запис извън масива; атаките, базирани на
това, целят презапис на адрес за връщане, SEH запис или heap указател, за да се
пренасочи управлението. DEP/NX забранява изпълнение на стека, ASLR разбърква
адресите, stack cookies и Control Flow Guard затрудняват пренасочването. Правилното
решение е да няма overflow, не да се заобикалят защитите.

```cpp
#include <iostream>
#include <string>

void safe(const std::string& input) {
    std::string buffer = input.substr(0, 8);     // граница, не char[8] + strcpy
    std::cout << buffer << '\n';
}

int main() {
    safe("this is too long for an 8-byte stack buffer");
}
```

#include <iostream>
#include <concepts>

using namespace std;

// Ограничител: T трябва да бъде числов тип
template <typename T>
concept Number = std::integral<T> || std::floating_point<T>;

// Функцията може да се използва само с Number
template <Number T>
T square(T x)
{
    return x * x;
}

int main()
{
    cout << square(5) << endl;       // int
    cout << square(2.5) << endl;     // double

    // cout << square("Hello") << endl; // Грешка: string не е Number

    return 0;
}
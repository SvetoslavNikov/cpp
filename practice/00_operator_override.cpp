#include <iostream>
#include <cstddef>

class MyType {
private:
    int value;

public:
    MyType(int v = 0) : value(v) {}

    // Unary arithmetic
    MyType operator+() const;
    MyType operator-() const;

    // Arithmetic
    MyType operator+(const MyType& other) const;
    MyType operator-(const MyType& other) const;
    MyType operator*(const MyType& other) const;
    MyType operator/(const MyType& other) const;
    MyType operator%(const MyType& other) const;

    // Comparison
    bool operator==(const MyType& other) const;
    bool operator!=(const MyType& other) const;
    bool operator<(const MyType& other) const;
    bool operator>(const MyType& other) const;
    bool operator<=(const MyType& other) const;
    bool operator>=(const MyType& other) const;

    // Assignment
    MyType& operator=(const MyType& other);
    MyType& operator+=(const MyType& other);
    MyType& operator-=(const MyType& other);
    MyType& operator*=(const MyType& other);
    MyType& operator/=(const MyType& other);
    MyType& operator%=(const MyType& other);

    // Increment / decrement
    MyType& operator++();       // ++x
    MyType operator++(int);     // x++
    MyType& operator--();       // --x
    MyType operator--(int);     // x--

    // Bitwise
    MyType operator~() const;
    MyType operator&(const MyType& other) const;
    MyType operator|(const MyType& other) const;
    MyType operator^(const MyType& other) const;
    MyType operator<<(int n) const;
    MyType operator>>(int n) const;

    // Bitwise assignment
    MyType& operator&=(const MyType& other);
    MyType& operator|=(const MyType& other);
    MyType& operator^=(const MyType& other);
    MyType& operator<<=(int n);
    MyType& operator>>=(int n);

    // Logical
    bool operator!() const;

    // Subscript
    int& operator[](std::size_t index);

    // Function call
    int operator()(int x) const;

    // Pointer-like access
    MyType* operator->();

    // Conversion
    operator bool() const;

    // Stream operators
    friend std::ostream& operator<<(std::ostream& out, const MyType& obj);
    friend std::istream& operator>>(std::istream& in, MyType& obj);
};
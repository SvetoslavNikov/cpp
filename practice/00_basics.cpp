#include <iostream>
using namespace std;

int main() {


//     T*     → pointer: "I have an address"
//
// T&     → lvalue reference: "another name for this existing object"
//
// T&&    → rvalue reference: "another name for this temporary/movable object"

    // ============================================================
    // 1. & in a DECLARATION = REFERENCE
    // ============================================================

    int x = 10;

    int& ref = x;          // ref is another name for x

    ref = 20;              // changes x too

    cout << x << "\n";     // 20
    cout << ref << "\n";   // 20


    // ============================================================
    // 2. & in an EXPRESSION = "ADDRESS OF"
    // ============================================================

    int y = 42;

    int* ptr = &y;         // &y = address of y

    cout << &y << "\n";    // memory address of y
    cout << ptr << "\n";   // same address


    // ============================================================
    // 3. * in a DECLARATION = POINTER
    // ============================================================

    int* p = &y;            // p is a pointer to an int

    // p stores an ADDRESS
    cout << p << "\n";     // address of y


    // ============================================================
    // 4. * in an EXPRESSION = DEREFERENCE
    // ============================================================

    cout << *p << "\n";    // 42

    // *p means:
    // "go to the address stored in p and get the value there"

    *p = 100;               // changes y

    cout << y << "\n";     // 100


    // ============================================================
    // 5. & AND * WORK TOGETHER
    // ============================================================

    int a = 50;

    int* p2 = &a;           // &a  -> address of a
    int  b  = *p2;          // *p2 -> value at that address

    cout << b << "\n";     // 50


    // ============================================================
    // 6. POINTER TO POINTER
    // ============================================================

    int n = 10;

    int* p3 = &n;           // p3 stores address of n
    int** pp = &p3;         // pp stores address of p3

    cout << n << "\n";      // 10
    cout << *p3 << "\n";    // 10
    cout << **pp << "\n";   // 10

    //        n
    //        |
    //        | address
    //        v
    //       p3
    //        |
    //        | address
    //        v
    //       pp


    // ============================================================
    // 7. & IN A FUNCTION PARAMETER = REFERENCE PARAMETER
    // ============================================================

    // This function can modify the original variable.
    auto doubleValue = [](int& value) {
        value *= 2;
    };

    int number = 5;

    doubleValue(number);

    cout << number << "\n"; // 10


    // ============================================================
    // 8. * IN A FUNCTION PARAMETER = POINTER PARAMETER
    // ============================================================

    auto tripleValue = [](int* value) {
        if (value != nullptr) {
            *value *= 3;
        }
    };

    int number2 = 5;

    tripleValue(&number2);  // pass address

    cout << number2 << "\n"; // 15


    // ============================================================
    // 9. & IN A FUNCTION RETURN TYPE = RETURNING A REFERENCE
    // ============================================================

    auto getReference = [](int& value) -> int& {
        return value;
    };

    int z = 7;

    int& r = getReference(z);

    r = 99;

    cout << z << "\n";      // 99


    // ============================================================
    // 10. * IN A FUNCTION RETURN TYPE = RETURNING A POINTER
    // ============================================================

    auto getPointer = [](int& value) -> int* {
        return &value;
    };

    int q = 123;

    int* pq = getPointer(q);

    *pq = 456;

    cout << q << "\n";      // 456


    // ============================================================
    // 11. & WITH STRUCT/CLASS OBJECTS
    // ============================================================

    struct Person {
        int age;
    };

    Person person{20};

    Person& personRef = person;  // reference
    Person* personPtr = &person; // pointer

    personRef.age = 21;
    personPtr->age = 22;

    cout << person.age << "\n";  // 22


    // ============================================================
    // 12. * WITH ARRAYS / POINTER ARITHMETIC
    // ============================================================

    int arr[] = {10, 20, 30};

    int* pa = arr;              // same as &arr[0]

    cout << *pa << "\n";         // 10
    cout << *(pa + 1) << "\n";   // 20
    cout << *(pa + 2) << "\n";   // 30


    // ============================================================
    // 13. * WITH MULTIPLE POINTERS
    // ============================================================

    int value = 500;

    int* p4 = &value;
    int** p5 = &p4;
    int*** p6 = &p5;

    cout << value << "\n";      // 500
    cout << *p4 << "\n";        // 500
    cout << **p5 << "\n";       // 500
    cout << ***p6 << "\n";      // 500


    // ============================================================
    // 14. & IN LOGICAL EXPRESSIONS = BITWISE AND
    // ============================================================

    int A = 6;   // binary: 110
    int B = 3;   // binary: 011

    cout << (A & B) << "\n";
    // 110
    // 011
    // ---
    // 010 = 2


    // ============================================================
    // 15. & WITH ASSIGNMENT = BITWISE AND ASSIGNMENT
    // ============================================================

    int C = 6;

    C &= 3;

    cout << C << "\n";   // 2


    // ============================================================
    // 16. * IN AN EXPRESSION = MULTIPLICATION
    // ============================================================

    int first = 5;
    int second = 4;

    int result = first * second;

    cout << result << "\n"; // 20


    // ============================================================
    // 17. * WITH ASSIGNMENT = MULTIPLICATION ASSIGNMENT
    // ============================================================

    int score = 10;

    score *= 5;

    cout << score << "\n"; // 50


    // ============================================================
    // 18. NEW + POINTER
    // ============================================================

    int* dynamicNumber = new int(42);

    cout << *dynamicNumber << "\n"; // 42

    *dynamicNumber = 100;

    cout << *dynamicNumber << "\n"; // 100

    delete dynamicNumber;


    // ============================================================
    // 19. POINTER CAN BE nullptr
    // ============================================================

    int* nothing = nullptr;

    if (nothing == nullptr) {
        cout << "Pointer points to nothing\n";
    }


    // ============================================================
    // 20. CONST + POINTER / REFERENCE
    // ============================================================

    const int constant = 10;

    // int* p = &constant;     // ERROR
    // Cannot use normal int* to point to const int.

    const int* pc = &constant;

    cout << *pc << "\n";       // 10

    // *pc = 20;               // ERROR
    // Can't modify constant through pc.


    // ============================================================
    // 21. POINTER TO CONST vs CONST POINTER
    // ============================================================

    int v1 = 10;
    int v2 = 20;

    const int* pointerToConst = &v1;

    // *pointerToConst = 30;   // ERROR
    pointerToConst = &v2;      // OK: pointer can change


    int* const constPointer = &v1;

    *constPointer = 30;        // OK: value can change

    // constPointer = &v2;     // ERROR: pointer can't change


    // ============================================================
    // THE BIG PICTURE
    // ============================================================

    /*

    & has several meanings:

        int& r = x;
         ^
         |
         +-- reference declaration

        int* p = &x;
                 ^
                 |
                 +-- address of x

        A & B
          ^
          |
          +-- bitwise AND


    * has several meanings:

        int* p;
           ^
           |
           +-- pointer declaration

        *p
         ^
         |
         +-- dereference pointer

        A * B
          ^
          |
          +-- multiplication


    The most important mental model:

        int x = 10;

        &x
        |
        +---- ADDRESS of x
                 |
                 v
        +----------------+
        |      10        |
        +----------------+
               x


        int* p = &x;

        p
        |
        +---- stores the ADDRESS of x
                       |
                       v
                 +----------+
                 |    10    |
                 +----------+
                       x


        *p
        |
        +---- "go to the address stored in p"
              and access the value there.


    So:

        &x  = "where is x?"
        *p  = "what is at the address in p?"


    */
}
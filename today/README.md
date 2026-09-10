# Separate C++ Files Example

This example demonstrates how a class is split into a header file and a source
file.

## Files

- `User.hpp` contains the class declaration: the public methods and private data.
- `User.h` is a compatibility header that includes `User.hpp`.
- `User.cpp` contains the definitions of the constructor, destructor, and
  `hello()` method.
- `main.cpp` creates `User` objects and calls their methods.

## `.h` versus `.hpp`

Both extensions are used for C++ header files. There is no technical difference
enforced by the compiler:

- `.h` is the older and more general convention. It may be used for C or C++.
- `.hpp` clearly communicates that the header contains C++ code, such as
  classes, templates, or namespaces.

This project uses `User.hpp` as the real header. `User.h` exists only as a
wrapper, so either include works:

```cpp
#include "User.hpp" // direct C++ header
#include "User.h"   // wrapper that includes User.hpp
```

## How It Works

`User first("Ivan")` calls the constructor. The object exists until the end of
`main()`, where its destructor is called automatically.

The second object is inside a smaller scope. Its destructor runs immediately at
the closing brace, before the first object is destroyed.

## Compile and Run

From the repository root:

```bash
c++ -std=c++17 today/main.cpp today/User.cpp -o today/app
./today/app
```

Expected output:

```text
Constructing Ivan
Hello, Ivan!
Constructing Maria
Hello, Maria!
Destroying Maria
Destroying Ivan
```

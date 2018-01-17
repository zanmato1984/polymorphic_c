# Polymorphic C


A C-implemented polymorphism framework. It demonstrates how polymorphism works using a pure procedural programming language.

It consists of 3 demos:

1. `cpp` directory contains a classic C++ polymorphism demo. It's pretty straight forward so no need to say more about it.

2. `c` directory contains the full C-expansion of the C++ case above. It shows how vtable is organize and managed, and how virtual function call happens, in a C fashion.

3. `pc` directory contains the frameworked version of the C case above. The polymorphic-c framework is actually implemented in file `polymorphic_c.h/c` and `main.c` shows how to use it.

Note this is a show-case project rather than a product. If you want to use polymorphism in your project, just choose an OOP language.

## Build

CMake

```sh
mkdir build
cd build
cmake ..
make [demo_cpp|demo_c|demo_pc]
```

## Features

1. Class define.
2. Inheritance.
3. User-defined ctor and dtor.
4. Virtual function define/override.

## Usage

See `pc/main.c`.

## Limitations

1. Max number of member functions in a single class is fixed.
2. User-defined ctor with parameters is not supported yet.
3. Function overload, both intra and inter-class, is not supported yet.
4. Access control is not supported yet.
5. Multi-inheritance is not supported yet.

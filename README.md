# Polymorphic C


A demonstrative C-implemented polymorphism framework. It shows how polymorphism works using a pure procedural programming language without extra parser or compiler involved.

This is a show-case project rather than a product. If you want to use polymorphism in your project, just choose an OOP language.

## Build

Windows: Visual Studio 2015

*nix: CMake

## Features

1. Class define.
2. Inheritance.
3. Virtual function define/override. 

## Usage

To use this framework, just include `polymorphic_c.h` in your .c file. Anything initial with double underscore are reserved symbols thus should not be used by users' code.

Interface to users consists of 90% macro and 10% function. They are named pretty straight forward so the demo `main.c` pretty much tells everything.

## Limitations

1. Max number of member functions in a single class is fixed.
2. Ctor and dtor are not supported yet.
3. Functions among different classes having the same name is not supported yet.
4. Access control is not supported yet.
5. Multi-inheritance is not supported yet.
6. The fact and the way of having to use macro `REGISTER_CLASS_VFUNCS` and `REGISTER_CLASSES` is cumbersome.

## The Grace Compiler

Grace is a hobby compiler written to experiment with the many ideas I have about how a compiler could be written, purely from an educational standpoint.

It is still a work-in-progress, and I intend to implement a new feature every week. Instructions to build and run are provided below. Subsequent commits will see the addition for a testing infrastructure, without which any reaonsably good codebase cannot do.


#### Building
The compiler is written in C++ and uses LLVM, and thus it is expected that LLVM libraries will be installed on the system, along with a C/C++ compiler that supports C++20, and an installation of CMake (Ninja is recommended for faster compiles).
To build, run:
```sh
cmake -Bbuild -GNinja -S.
cmake --build build
```

This should produce a binary called `grcc` in the `build` folder. The binary does not accept any input as of now, and is their only as glue code. It will become the entrypoint as the Grace compiler picks up pace.
To run the binary, simply execute:
```sh
./build/grcc
```

which should produce something like this:
```
{Token: {TokenType: {Constant: {Float: 23.440000}}}}
{Token: {TokenType: Star}}
{Token: {TokenType: Slash}}
{Token: {TokenType: {Constant: {Integer: 1}}}}
{Token: {TokenType: Plus}}
{Token: {TokenType: {Constant: {Integer: 1}}}}
{Token: {TokenType: Plus}}
{Token: {TokenType: {Constant: {Float: 1.110000}}}}
{Token: {TokenType: Eof}}
[END]
```

And voila! Grace has lexed (all it can do for now) the input string passed to it in `grace.cc`.


#### Approach
The compiler's implementation process is intended to be what I call _end-to-end incremental_. It will start by lexing arithmetic expressions, followed by parsing and code-generation for the same.
This is a very neat approach in my opinion, and more can be read about this in the [original paper](http://scheme2006.cs.uchicago.edu/11-ghuloum.pdf) which introduced it.

Any information I find useful will be added as a reference.

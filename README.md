## The Grace VM

Grace is an imperative programming language with first-class support for functions. It is implemented as a stack-based bytecode compiler. The language spec targets simplicity and ease-of-use while still providing a reasonable guarantee of safety.

The core of the Grace VM is implemented in C. The compiler (in future versions) will also implement a standard library, which will be implemented mostly in Grace itself and will live in `src/stdlib`.

Grace program files end with extension `grc`. The compiler does not yet implement a module system, so the file source must be implemented in a single file.


### Building the source

The build system for the Grace compiler uses `bazel`, and the preferred and recommended installation channel is `bazelisk`. To build the compiler binary, `grc`, run:

```sh
$ bazelisk build :grc
```

This command should produce the `grc` binary under the path `./bazel-bin/grc` relative to the top-level directory.

### Testing
We use the GTest framework for unit-testing the compiler's source code. Tests can be run with:
```sh
$ bazelisk test //tests:grc_tests
```
which will run the whole test-suite. The build system will soon be able to support running independent test-sets separately, so that isolated changes do not require running the while test-suite.

### The design of the language

Following is an example program in Grace:
```
fn main() {
    // `a` is a let binding that binds to a _function_.
    let a = fn(a, b) {
        a + b
    }

    print(test(a, 2, 3)); // prints `5` to the console.
}

fn test(f, a, b) {
    return f(a, b);
}
```

The syntax is similar in look to C. It supports binding functions to variables and passing them as first-class entities. The type-system is dynamic, but aims to be strongly-typed and goes to great lengths to avoid C-like implicit conversions, and hidden/unexpected behavioral semantics.

### Contributing
Any and all contributions are welcome! If you find a bug in Grace, or would like to extend the VM to support a cool feature, please file an issue! We would love to hear your opinions.

All PR authors are encouraged to file an issue before they start working on their patch, to help with tracking all the changes that are merged into the compiler.

We request that large PRs be split across multiple smaller ones, each containing the smallest independent and functional change, as this makes the review process much easier. Please _ensure_ that all patches are accompanied by unit-tests that cover most obvious edge cases, as that helps reduce the amount of error-prone code that makes its way into the codebase.

For doc-writers, all docs should go in `grace/docs`. Developers should use `///` (doc-comments) for writing descriptive comments that will be used to generate documentation (through `doxygen`) and for listing by LSP servers. All internal notes/comments in the code are listed by `//` comments.

#### Formatting

It is required that all patches are formatted before they are sent for review. A pre-commit hook is provided for convenience. This will run when you commit the code, and will ensure that formatter is run automatically.

```sh
$ python3 -m venv </path/to/venv/>
$ source /path/to/venv/bin/activate ## Activate.psh for powershell users, and activate.fish for Fish.
$ python3 -m pip install pre-commit && pre-commit install
```

The `git-clang-format` command also integrates well with `clang-format`, but you might need to amend the previous commit.

```sh
$ git-clang-format HEAD~ && git commit --amend -a
```

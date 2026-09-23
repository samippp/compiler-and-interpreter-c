# C → x86-64 Compiler

A small compiler, written from scratch in C++, that translates a subset of C into x86-64 assembly (AT&T syntax). I built it to understand what happens between source code and the CPU: how text becomes tokens, how tokens become a tree, and how a tree becomes instructions.

No parser generators or compiler libraries. The lexer, parser, AST, and code generator are all hand-written.

## Example

Input (`test.c`):

```c
int main() {
    return 2 * (3 + 4) - !0;
}
```

Output (x86-64 assembly):

```asm
    .text
    .globl _main
_main:
    movl    $2, %eax
    pushq   %rax
    movl    $3, %eax
    pushq   %rax
    movl    $4, %eax
    popq    %rcx
    addl    %ecx, %eax
    popq    %rcx
    imul    %ecx, %eax
    pushq   %rax
    movl    $0, %eax
    cmpl    $0, %eax
    movl    $0, %eax
    sete    %al
    popq    %rcx
    subl    %ecx, %eax
    ret
```

> TODO: replace this with real output copied from your compiler.

## How it works

```
source.c ──► Lexer ──► tokens ──► Parser ──► AST ──► Code generator ──► assembly.s
```

| Stage | File | What it does |
|---|---|---|
| Lexer | `lexer.cpp`, `Token.h` | Splits source into 25 token types: keywords, identifiers, literals, and single- and multi-character operators like `&&`, `<=`, `!=` |
| Parser | `parser.cpp` | Recursive-descent parser with one function per precedence level, so `1 + 2 * 3` and `1 - 2 - 3` get the right precedence and left associativity |
| AST | `tree.cpp`, `tree.h` | Program → Function → Statement → Expression nodes |
| Code generation | `code_generation.cpp` | Walks the AST and emits stack-based x86-64: evaluate the left operand, push it, evaluate the right, pop, and combine |

### Supported language features

- `int main()` with a `return` statement
- Unary operators: `-`, `~`, `!`
- Arithmetic: `+`, `-`, `*`, `/`, `%`
- Relational: `==`, `!=`, `<`, `<=`, `>`, `>=`
- Logical: `&&`, `||` with **short-circuit evaluation** (emitted as conditional jumps)
- Parenthesized and nested expressions with correct precedence and associativity

### Interesting details

- **Division and modulo** use `cdq` to sign-extend `%eax` into `%edx:%eax` before `idivl`. The remainder for `%` comes from `%edx`.
- **Comparisons** use `cmpl` followed by `setCC %al`, which turns CPU flags into a 0/1 value.
- **Short-circuiting** `&&` and `||` jump past the right-hand operand once the result is known, so `0 && f()` never evaluates `f()`.

## Build & run

```bash
# TODO: fill in the exact commands once there is a single entry point
g++ -std=c++17 -o compiler lexer.cpp parser.cpp tree.cpp Token.cpp code_generation.cpp
./compiler program.c        # writes program.s
gcc program.s -o program    # assemble and link
./program; echo $?          # the exit code is the return value
```

## Testing

Tested against [Nora Sandler's "Write a C Compiler" test suite](https://github.com/nlsandler/write_a_c_compiler). Each stage has valid programs, which must compile and run correctly, and invalid ones, which must be rejected.

```bash
./test_compiler.sh ./compiler 1 2 3 4
```

## Roadmap

- [ ] Local variables and assignment (stack frames with `%rbp` offsets)
- [ ] `if` / `else` and the ternary operator
- [ ] Loops: `for`, `while`, `do`, `break`, `continue`
- [ ] Function calls following the System V calling convention, including recursion

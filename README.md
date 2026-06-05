# libasm

For this 42 project, I needed to implement core C standard library functions in **x86-64 assembly language**. It made me feel like I was actually talking the computer's language instead of a human-translated, dumbed-down version of it.

## What is Assembly?

Assembly is a symbolic representation of machine code: the instructions that CPUs directly execute. So when writing in assembly, nearly all instruction that we write is exactly one binary machine code instruction!

To help understand:

Assembly Language:
```
xor rax, rax
```
Hexadecimal Machine Code:
```
48 31 C0
```
Binary Machine Code:
```
01001000 00110001 11000000
```

Here's how the translation process works:

```
┌─────────────┐    compile    ┌────────────┐   assemble    ┌──────────────┐    link   ┌ ────────────────┐
│   C Code    │─────────────→ │ Assembly   │─────────────→ │ Machine Code │─────────→ │ Running Program │
│ (readable)  │               │ (readable) │               │ (binary)     │           │   (CPU exec)    │
└─────────────┘               └────────────┘               └──────────────┘           └─────────────────┘
```

**Key differences with C:**
- NO ABSTRACTIONS: You manage memory, registers, and CPU operations directly. You see exactly how the CPU interacts with memory.
- OPERATIONS ARE EXPLICIT: Every memory load, every calculation, every function call is visible
- REGISTERS: Values live in CPU registers (rax, rbx, rdi, etc.) rather than automatic memory allocation


### Assembly Formatting

Each `.s` file follows this pattern:

```asm
bits 64               ; Use 64-bit architecture

global ft_function    ; Export function (make it callable from C)

section .text         ; Code section

ft_function:
    ; Assembly instructions here
    ret               ; Return to caller
```


### Example: ft_strlen in Assembly vs C

**in C:**
```c
size_t ft_strlen(const char *str) {
    size_t i = 0;
    while (str[i] != '\0')
        i++;
    return i;
}
```

**in Assembly x86-64:**
```asm
ft_strlen:
    xor rax, rax        ; rax = 0 (loop counter)
.loop:
    cmp BYTE [rdi + rax], 0  ; check if character is null terminator
    je .end             ; if equal, jump to end
    inc rax              ; increment counter
    jmp .loop            ; loop again
.end:
    ret                 ; return rax
```

Both do the same thing, but assembly shows exactly what the CPU is doing at each step.

## Building

```bash
make
```

This creates `libasm.a`, a static library containing all assembly functions.

## Clean
```bash
make clean      # Remove object files
make fclean     # Remove everything
make re         # Clean and rebuild
```

## Testing

Run the test suite:
```bash
make test
```

This compiles C code that calls your assembly functions and compares outputs with the standard C library versions. If everything works, you'll see matching results for each function.

## Key registers used:

| Register | Purpose | Saved across calls? |
|----------|---------|------|
| `rax` | Return value, accumulator | no |
| `rdi` | First function argument | yes |
| `rsi` | Second function argument | no |
| `rdx` | Third function argument | no |
| `rcx` | Fourth function argument, loop counter | no |
| `rsp` | Stack pointer (to top of stack) | yes |
| `r8` | Fifth function argument | no |
| `r9` | Sixth function argument | no |
| `r10-r11` | Temporary registers | no |
| `r12-r15` | Callee-saved registers | yes |


**IMPORTANT:** The first 6 integer arguments are passed in registers (System V AMD64 ABI calling convention), not on the stack.


## Resources
- [Amazing Cheatsheet](https://cs.brown.edu/courses/cs033/docs/guides/x64_cheatsheet.pdf)
- [NASM Assembly Tutorial with beginner-friendly examples](https://cs.lmu.edu/~ray/notes/nasmtutorial/)

- [Syscalls table](https://x64.syscall.sh/)
- [__errno_location()](http://refspecs.linux-foundation.org/LSB_4.1.0/LSB-Core-generic/LSB-Core-generic/baselib---errno-location.html)
- [Understanding errno better](https://www.reddit.com/r/C_Programming/comments/p9wg02/trouble_understanding_errno/)
- [Calling Functions in Assembly](https://www.cs.uaf.edu/2017/fall/cs301/lecture/09_06_functions.html)
- [Stack alignment - see page 16](https://refspecs.linuxbase.org/elf/x86_64-abi-0.99.pdf)

# libasm

A learning project implementing core C standard library functions in **x86-64 assembly language**. This project bridges the gap between high-level C code and low-level machine execution, helping understand how computers actually run code.

## What is Assembly?

Assembly is a symbolic representation of **machine code**—the instructions that CPUs directly execute. Here's how the translation process works:

```
┌─────────────┐    compile    ┌────────────┐   assemble   ┌──────────────┐    link    ┌ ────────────────┐
│   C Code    │─────────────→ │ Assembly   │─────────────→ │ Machine Code │─────────→ │ Running Program │
│ (readable)  │               │ (readable) │               │ (binary)     │           │   (CPU exec)    │
└─────────────┘               └────────────┘               └──────────────┘           └─────────────────┘
```

**Key differences from C:**
- **No abstractions**: You manage memory, registers, and CPU operations directly
- **Explicit operations**: Every memory load, every calculation, every function call is visible
- **Register-based**: Values live in CPU registers (rax, rbx, rdi, etc.) rather than automatic memory allocation
- **Hardware-aware**: You see exactly how the CPU and memory interact

### Example: `ft_strlen` in Assembly vs C

**C version:**
```c
size_t ft_strlen(const char *str) {
    size_t i = 0;
    while (str[i] != '\0')
        i++;
    return i;
}
```

**Assembly version:**
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

Both do the same thing, but assembly shows **exactly** what the CPU is doing at each step.

## Building

### Requirements
- `nasm` (Netwide Assembler)
- `gcc` or `clang`
- `make`

### Compile
```bash
make
```

This creates `libasm.a`, a static library containing all assembly functions.

### Clean
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

## Understanding the Code

### x86-64 Register Overview

Key registers used in this project:

| Register | Purpose | Size |
|----------|---------|------|
| `rax` | Return value, accumulator | 64-bit |
| `rdi` | First function argument | 64-bit |
| `rsi` | Second function argument | 64-bit |
| `rdx` | Third function argument | 64-bit |
| `rcx` | Fourth function argument, loop counter | 64-bit |

**Note:** The first 6 integer arguments are passed in registers (System V AMD64 ABI calling convention), not on the stack.

### Assembly File Format

Each `.s` file follows this pattern:

```asm
bits 64               ; Use 64-bit architecture

global ft_function    ; Export function (make it callable from C)

section .text         ; Code section

ft_function:
    ; Assembly instructions here
    ret               ; Return to caller
```

## Resources

- [x86-64 Instruction Set Reference](https://www.felixcloutier.com/x86/)
- [System V AMD64 ABI](https://refspecs.linuxbase.org/elf/x86_64-abi-0.99.pdf)
- [NASM Assembly Language Tutorial](https://cs.lmu.edu/~ray/notes/nasmtutorial/)

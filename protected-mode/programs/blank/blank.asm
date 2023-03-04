[BITS 32]
global _start

section .asm
_start:
    push 20
    push 30
    mov eax, 0 ; Command 0 Sum
    int 0x80
    add esp, 8
    jmp $
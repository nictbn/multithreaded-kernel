[BITS 32]
global _start

section .asm
_start:
    mov eax, 0
    int 0x80
    jmp $
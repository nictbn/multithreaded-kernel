[BITS 32]
global _start

section .asm
_start:
    push message
    mov eax, 1 ; Print command
    int 0x80
    add esp, 4
    jmp $
section .data
message: db 'I can talk with the kernel', 0
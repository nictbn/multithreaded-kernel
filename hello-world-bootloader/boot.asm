ORG 0x7C00
BITS 16

start:
    mov si, message
    call print
    jmp $
print:
    mov bx, 0
.loop:
    lodsb
    cmp al, 0
    je .done
    call print_char
    jmp .loop
.done:
    ret

print_char:
    mov ah, 0eh
    int 0X10
    ret

message: db 'Hello World!', 0

times 510- ($ - $$) db 0
dw 0XAA55
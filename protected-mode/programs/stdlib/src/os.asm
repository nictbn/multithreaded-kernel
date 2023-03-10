[BITS 32]
section .asm
global print:function
global os_getkey:function
global os_malloc:function
global os_free:function
global os_putchar:function
global os_process_load_start:function
global os_system:function
global os_process_get_arguments:function
global os_exit:function

print:
    push ebp
    mov ebp, esp
    push dword[ebp + 8]
    mov eax, 1
    int 0x80
    add esp, 4
    pop ebp
    ret

os_getkey:
    push ebp
    mov ebp, esp
    mov eax, 2
    int 0x80
    pop ebp
    ret

os_malloc:
    push ebp
    mov ebp, esp
    mov eax, 4
    push dword[ebp + 8]
    int 0x80
    add esp, 4
    pop ebp
    ret

os_free:
    push ebp
    mov ebp, esp
    mov eax, 5
    push dword[ebp + 8]
    int 0x80
    add esp, 4
    pop ebp
    ret

os_putchar:
    push ebp
    mov ebp, esp
    mov eax, 3
    push dword[ebp + 8]
    int 0x80
    add esp, 4
    pop ebp
    ret

os_process_load_start:
    push ebp
    mov ebp, esp
    mov eax, 6
    push dword[ebp + 8]
    int 0x80
    add esp, 4
    pop ebp
    ret

os_system:
    push ebp
    mov ebp, esp
    mov eax, 7 ; Command 7 process_system ( runs a system command based on the arguments)
    push dword[ebp+8]
    int 0x80
    add esp, 4
    pop ebp
    ret

os_process_get_arguments:
    push ebp
    mov ebp, esp
    mov eax, 8 
    push dword[ebp+8]
    int 0x80
    add esp, 4
    pop ebp
    ret

os_exit:
    push ebp
    mov ebp, esp
    mov eax, 9
    int 0x80
    pop ebp
    ret
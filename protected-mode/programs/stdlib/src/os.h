#include <stddef.h>
#include <stdbool.h>
#ifndef OS_H
#define OS_H
void print(const char* filename);
int os_getkey();
void* os_malloc(size_t size);
void os_free(void* ptr);
void os_putchar(char c);
int os_getkey_block();
void os_terminal_readline(char* out, int max, bool output_while_typing);
void os_process_load_start(const char* filename);
#endif
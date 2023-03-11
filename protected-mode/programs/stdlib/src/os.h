#include <stddef.h>
#ifndef OS_H
#define OS_H
void print(const char* filename);
int getkey();
void* os_malloc(size_t size);
void os_free(void* ptr);
#endif
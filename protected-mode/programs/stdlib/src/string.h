#ifndef OS_STRING_H
#define OS_STRING_H
#include <stdbool.h>

int strlen(const char* ptr);
int strnlen(const char* ptr, int max);
bool is_digit(char c);
int to_numeric_digit(char c);
char* strcpy(char* dest, const char* src);
char* strncpy(char* dest, const char* src, int count);
int strnlen_terminaor(const char* ptr, int max, char terminator);
char tolower(char s1);
int istrncmp(const char* s1, const char* s2, int n);
int strncmp(const char* str1, const char* str2, int n);
char* strtok(char* str, const char* delimiters);
#endif
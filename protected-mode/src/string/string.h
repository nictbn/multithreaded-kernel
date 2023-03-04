#ifndef STRING_H
#define STRING_H

#include <stdbool.h>

int strlen(const char* ptr);
bool is_digit(char c);
int to_numeric_digit(char c);
int strnlen(const char* ptr, int max);
char* strcpy(char* dest, const char* src);
int strncmp(const char* str1, const char* str2, int n);
int istrncmp(const char* s1, const char* s2, int n);
int strnlen_terminaor(const char* ptr, int max, char terminator);
char tolower(char s1);
char* strncpy(char* dest, const char* src, int count);
#endif
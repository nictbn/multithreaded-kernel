#include "string.h"

int strlen(const char* ptr) {
    int i = 0;
    while (*ptr != 0) {
        i++;
        ptr++;
    }
    return i;
}

int strnlen(const char* ptr, int max) {
    int i = 0;
    for (i = 0; i < max; i++) {
        if (ptr[i] == 0) {
            break;;
        }
    }
    return i;
}

bool is_digit(char c) {
    return c >= 48 && c <= 57;
}

int to_numeric_digit(char c) {
    return c - 48;
}

char* strcpy(char* dest, const char* src) {
    char* res = dest;
    while (*src != 0) {
        *dest = *src;
        src += 1;
        dest += 1;
    }
    *dest = 0x00;
    return res;
}

char* strncpy(char* dest, const char* src, int count) {
    int i = 0;
    for (i = 0; i < count - 1; i++) {
        if (src[i] == 0x00) {
            break;
        }
        dest[i] = src[i];
    }
    dest[i] = 0x00;
    return dest;
}

int strnlen_terminaor(const char* ptr, int max, char terminator) {
    int i = 0;
    for (i = 0; i < max; i++) {
        if (ptr[i] == '\0' || ptr[i] == terminator) {
            break;
        }
    }
    return i;
}

char tolower(char s1) {
    if (s1 >= 65 && s1 <= 90) {
        s1 += 32;
    }
    return s1;
}

int istrncmp(const char* s1, const char* s2, int n) {
    unsigned char u1, u2;
    while(n-- > 0) {
        u1 = (unsigned char)*s1++;
        u2 = (unsigned char)*s2++;
        if (u1 != u2 && tolower(u1) != tolower(u2)) {
            return u1 - u2;
        }
        if (u1 == '\0') {
            return 0;
        }
    }
    return 0;
}

int strncmp(const char* str1, const char* str2, int n) {
    unsigned char u1, u2;
    while (n-- > 0) {
        u1 = (unsigned char)*str1++;
        u2 = (unsigned char)*str2++;
        
        if (u1 != u2) {
            return u1 - u2;
        }

        if (u1 == '\0') {
            return 0;
        }
    }
    return 0;
}

char* sp = 0;
char* strtok(char* str, const char* delimiters) {
    int i = 0;
    int len = strlen(delimiters);
    if (!str && !sp) {
        return 0;
    }

    if (str && !sp) {
        sp = str;
    }

    char* p_start = sp;
    while (1) {
        for (i = 0; i < len; i++) {
            if (*p_start == delimiters[i]) {
                p_start++;
                break;
            }
        }
        if (i == len) {
            sp = p_start;
            break;
        }
    }

    if (*sp == '\0') {
        sp = 0;
        return sp;
    }

    // find end of substring

    while (*sp != '\0') {
        for (i = 0; i < len; i++) {
            if (*sp == delimiters[i]) {
                *sp = '\0';
                break;
            }
        }
        sp++;
        if (i < len) {
            break;
        }
    }
    return p_start;
}
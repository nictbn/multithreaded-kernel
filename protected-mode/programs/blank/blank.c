#include "os.h"
#include "stdlib.h"
#include "stdio.h"
#include "string.h"

int main (int argc, char** argv) {
    printf("The meaning of life and everything is %i\n", 42);
    char words[] = "hello how are you";
    const char* token = strtok(words, " ");
    while(token) {
        printf("%s\n", token);
        token = strtok(NULL, " ");
    }
    while(1) {}
    return 0;
}
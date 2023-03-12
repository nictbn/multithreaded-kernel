#include "os.h"
#include "stdlib.h"
#include "stdio.h"
#include "string.h"

int main (int argc, char** argv) {
    printf("The meaning of life and everything is %i\n", 42);
    char* ptr = malloc(20);
    strcpy(ptr, "hello world");
    print(ptr);
    while(1) {}
    return 0;
}
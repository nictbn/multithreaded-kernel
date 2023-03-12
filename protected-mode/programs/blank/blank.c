#include "os.h"
#include "stdlib.h"
#include "stdio.h"
#include "string.h"

int main (int argc, char** argv) {
    printf("The meaning of life and everything is %i\n", 42);
    for (int i = 0; i < argc; i++) {
        printf("%s\n", argv[i]);
    }

    char* ptr = (char*) 0x00;
    *ptr = 0x50;
    while(1) {}
    return 0;
}
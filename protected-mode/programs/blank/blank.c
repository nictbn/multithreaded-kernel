#include "os.h"
#include "stdlib.h"
#include "stdio.h"
#include "string.h"

int main (int argc, char** argv) {
    printf("The meaning of life and everything is %i\n", 42);

    struct process_arguments arguments;
    os_process_get_arguments(&arguments);
    printf("%i %s\n", arguments.argc, arguments.argv[0]);
    while(1) {}
    return 0;
}
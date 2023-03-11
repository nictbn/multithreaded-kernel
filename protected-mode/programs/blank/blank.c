#include "os.h"
#include "stdlib.h"
int main (int argc, char** argv) {
    print("Hello, how are you?\n");
    void* ptr = malloc(512);
    if (!ptr) {
        print("Error, could not allocate memory\n");
    }

    while(1) {
        if (getkey() != 0) {
            print("Key was pressed!\n");
        }
    }
    return 0;
}
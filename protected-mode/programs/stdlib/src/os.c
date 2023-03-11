#include "os.h"
int os_getkey_block() {
    int val = 0;
    do {
        val = os_getkey();
    } while (val == 0); 
    return val;
}

void os_terminal_readline(char* out, int max, bool output_while_typing) {
    int i = 0;
    for (i = 0; i < max - 1; i++) {
        char key = os_getkey_block();
        // carriage return
        if (key == 13) {
            break;
        }
        if (output_while_typing) {
            os_putchar(key);
        }
        // backspace
        if (key == 0x08 && i >= 1) {
            out[i - 1] = 0x00;
            i -= 2;
            continue;
        }
        out[i] = key;
    }
    out[i] = 0x00;
}
#include "io.h"
#include "task/task.h"
#include "kernel.h"
#include "keyboard/keyboard.h"
void* isr80h_command1_print(struct interrupt_frame* frame) {
    void* user_space_msg_buffer = task_get_stack_item(task_current(), 0);
    char buf[1024];
    copy_string_from_task(task_current(), user_space_msg_buffer, buf, sizeof(buf));
    print(buf);
    return 0;
}

void* isr80h_comand2_get_key(struct interrupt_frame* frame) {
    char c = keyboard_pop();
    return (void*) ((int)c);
}

void* isr80h_comand3_put_char(struct interrupt_frame* frame) {
    char c = (char)(int)task_get_stack_item(task_current(), 0);
    terminal_write_char(c, 15);
    return 0;
}
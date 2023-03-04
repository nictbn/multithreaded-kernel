#include "misc.h"
#include "idt/idt.h"
#include "task/task.h"

void* isr80h_command0_sum(struct interrupt_frame* frame) {
    int v1 = (int) task_get_stack_item(task_current(), 0);
    int v2 = (int) task_get_stack_item(task_current(), 1);
    return (void*) (v1 + v2);
}
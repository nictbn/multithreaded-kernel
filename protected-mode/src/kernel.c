#include "kernel.h"
#include <stdint.h>
#include <stddef.h>
#include "idt/idt.h"
#include "io/io.h"
#include "memory/heap/kheap.h"
#include "memory/paging/paging.h"
#include "disk/disk.h"
#include "fs/pparser.h"
#include "string/string.h"
#include "disk/streamer.h"
#include "string/string.h"
#include "fs/file.h"
#include "gdt/gdt.h"
#include "config.h"
#include "status.h"
#include "memory/memory.h"
#include "task/tss.h"
#include "task/task.h"
#include "task/process.h"
#include "isr80h/isr80h.h"
#include "keyboard/keyboard.h"

uint16_t* video_mem = 0;
uint16_t terminal_row = 0;
uint16_t terminal_col = 0;

uint16_t terminal_make_char(char c, char colour) {
    return (colour << 8) | c;
}

void terminal_putchar(int x, int y, char c, char colour) {
    video_mem[y * VGA_WIDTH + x] = terminal_make_char(c, colour);
}

void terminal_backspace() {
    if (terminal_row == 0 && terminal_col == 0) {
        return;
    }
    if (terminal_col == 0) {
        terminal_row -= 1;
        terminal_col = VGA_WIDTH;
    }

    terminal_col -= 1;
    terminal_write_char(' ', 15);
    terminal_col -= 1;
}

void terminal_write_char(char c, char colour) {
    if (c == '\n') {
        terminal_row++;
        terminal_col = 0;
        return;
    }

    if (c == 0x08) {
        terminal_backspace();
        return;
    }

    terminal_putchar(terminal_col, terminal_row, c, colour);
    terminal_col++;
    if (terminal_col >= VGA_WIDTH) {
        terminal_row++;
        terminal_col = 0;
    }
}

void terminal_initialize() {
    terminal_row = 0;
    terminal_col = 0;
    video_mem = (uint16_t*)(0xB8000);
    for (int y = 0; y < VGA_HEIGHT; y++) {
        for (int x = 0; x < VGA_WIDTH; x++) {
            terminal_putchar(x, y, ' ', 0);
        }
    }
}

void print(const char* str) {
    size_t len = strlen(str);
    for (int i = 0; i < len; i++) {
        terminal_write_char(str[i], 15);
    }
}

static struct paging_4gb_chunk*  kernel_chunk = 0;

void panic(const char* msg) {
    print(msg);
    while(1) {}
}

void kernel_page() {
    kernel_registers();
    paging_switch(kernel_chunk);
}

struct tss tss;

struct gdt gdt_real[OS_TOTAL_GDT_SEGMENTS];
struct gdt_structured gdt_structured[OS_TOTAL_GDT_SEGMENTS] = {
    {.base = 0x00, .limit = 0x00, .type = 0x00}, // null segment
    {.base = 0x00, .limit = 0xFFFFFFFF, .type = 0x9A}, // kernel code segment
    {.base = 0x00, .limit = 0xFFFFFFFF, .type = 0x92}, // kernel data segment
    {.base = 0x00, .limit = 0xFFFFFFFF, .type = 0xF8}, // user code segment
    {.base = 0x00, .limit = 0xFFFFFFFF, .type = 0xF2}, // user data segment
    {.base = (uint32_t)&tss, .limit = sizeof(tss), .type = 0xE9}, //tss segment
};

void kernel_main() {
    terminal_initialize();

    memset(gdt_real, 0x00, sizeof(gdt_real));
    gdt_structured_to_gdt(gdt_real, gdt_structured, OS_TOTAL_GDT_SEGMENTS);

    // load the gdt
    gdt_load(gdt_real, sizeof(gdt_real));

    // initialize the heap
    kheap_init();

    // Initialize filesystems
    fs_init();

    // search and initialize the disks
    disk_search_and_init();

    // initialize the interrupt descriptor table
    idt_init();

    // setup the tss
    memset(&tss, 0x00, sizeof(tss));
    tss.esp0 = 0x600000;
    tss.ss0 = KERNEL_DATA_SELECTOR;

    // load the tss
    tss_load(0x28);

    // setup paging
    kernel_chunk = paging_new_4gb(PAGING_IS_WRITEABLE | PAGING_IS_PRESENT | PAGING_ACCESS_FROM_ALL);

    // switch to kernel paging chunk
    
    paging_switch(kernel_chunk);

    // enable paging
    enable_paging();

    // register the kernel commands
    isr80h_register_commands();

    // initialize all the system keyboards
    keyboard_init();

    struct process* process = 0;
    int res = process_load_switch("0:/shell.elf", &process);
    if (res != OS_ALL_OK) {
        panic("Failed to load blank.elf\n");
    }
    
    task_run_first_ever_task();
    while (1) {}
}
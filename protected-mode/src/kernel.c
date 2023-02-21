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
#include "memory/memory.h"
#include "task/tss.h"

uint16_t* video_mem = 0;
uint16_t terminal_row = 0;
uint16_t terminal_col = 0;

uint16_t terminal_make_char(char c, char colour) {
    return (colour << 8) | c;
}

void terminal_putchar(int x, int y, char c, char colour) {
    video_mem[y * VGA_WIDTH + x] = terminal_make_char(c, colour);
}

void terminal_write_char(char c, char colour) {
    if (c == '\n') {
        terminal_row++;
        terminal_col = 0;
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
    print("Hello World!\ntest");

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
    uint32_t* directory = paging_4gb_chunk_get_directory(kernel_chunk);
    paging_switch(directory);

    // enable paging
    enable_paging();

    // enable interrupts
    enable_interrupts();

    int fd = fopen("0:/hello.txt", "r");
    if (fd) {
        struct file_stat s;
        fstat(fd, &s);
        fclose(fd);
        print("testing\n");
    }
    while (1) {}
}
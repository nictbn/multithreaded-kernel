#ifndef PROCESS_H
#define PROCESS_H
#include <stdint.h>
#include "task.h"
#include "config.h"
#include <stdbool.h>

#define PROCESS_FILETYPE_ELF 0
#define PROCESS_FILETYPE_BINARY 1

typedef unsigned char PROCESS_FILETYPE;
struct process_allocation {
    void* ptr;
    size_t size;
};

struct process {
    // the process id
    uint16_t id;
    char filename[OS_MAX_PATH];
    // the main process task
    struct task* task;

    // the memory (malloc) allocations of the process
    struct process_allocation allocations[OS_MAX_PROGRAM_ALLOCATIONS];

    PROCESS_FILETYPE filetype;
    union {
        // the physical pointer to the process memory;
        void* ptr;

        struct elf_file* elf_file;
    };

    // the physical pointer to the stack memory
    void* stack;
    
    // the size of the data pointed to by "ptr"
    uint32_t size;

    struct keyboard_buffer {
        char buffer[OS_KEYBOARD_BUFFER_SIZE];
        int tail;
        int head;
    } keyboard;
};
int process_switch(struct process* process);
int process_load_switch(const char* filename, struct process** process);
int process_load(const char* filename, struct process** process);
int process_load_for_slot(const char* filename, struct process** process, int process_slot);
struct process* process_current();
struct process* process_get(int process_id);
void* process_malloc(struct process* process, size_t size);
void process_free(struct process* process, void* ptr);
#endif
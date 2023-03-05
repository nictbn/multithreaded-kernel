#ifndef ELFLOADER_H
#define ELFLOADER_H

#include <stdint.h>
#include <stddef.h>

#include "elf.h"
#include "config.h"

struct elf_file {
    char filename[OS_MAX_PATH];
    int in_memory_size;

    // pointer to the physical address where the elf file is loaded
    void* elf_memory;

    // the virtual base address of this binary
    void* virtual_base_address;

    // the ending virtual address of this binary
    void* virtual_end_address;

    // the physical base address of this binary
    void* physical_base_address;

    // the ending physical address of this binary
    void* physical_end_address;

};

#endif
#ifndef CONFIG_H
#define CONFIG_H
#define OS_TOTAL_INTERRUPTS 512
#define KERNEL_CODE_SELECTOR 0x08
#define KERNEL_DATA_SELECTOR 0x10
// 100 MB heap
#define OS_HEAP_SIZE_BYTES 104857600
#define OS_HEAP_BLOCK_SIZE 4096
#define OS_HEAP_ADDRESS 0x01000000
#define OS_HEAP_TABLE_ADDRESS 0x00007E00
#define OS_SECTOR_SIZE 512
#define OS_MAX_PATH 108
#define OS_MAX_FILESYSTEMS 12
#define OS_MAX_FILE_DESCRIPTORS 512
#define OS_TOTAL_GDT_SEGMENTS 6
#define OS_PROGRAM_VIRTUAL_ADDRESS 0x400000
#define OS_USER_PROGRAM_STACK_SIZE 1024 * 16 // 16 KB stack
#define OS_PROGRAM_VIRTUAL_STACK_ADDRESS_START 0x3FF000
#define OS_PROGRAM_VIRTUAL_STACK_ADDRESS_END OS_PROGRAM_VIRTUAL_STACK_ADDRESS_START - OS_USER_PROGRAM_STACK_SIZE
#define USER_DATA_SEGMENT 0x23
#define USER_CODE_SEGMENT 0x1B
#define OS_MAX_PROGRAM_ALLOCATIONS 1024
#define OS_MAX_PROCESSES 12
#define OS_MAX_ISR80H_COMMANDS 1024

#endif
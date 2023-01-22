#ifndef IDT_H
#define IDT_H
#include <stdint.h>
// https://wiki.osdev.org/Interrupt_Descriptor_Table
struct idt_desc {
    uint16_t offset_1; // offset bits 0 - 15
    uint16_t selector; // selector that's in our GDT
    uint8_t zero; // does nothing, set to zero
    uint8_t type_attr; // Descriptor type and attributes
    uint16_t offset_2; // offset upper bits
}__attribute__((packed));

struct idtr_desc {
    uint16_t limit; // size of descriptor table - 1
    uint32_t base; // base address of the start of the interrupt descriptor table
}__attribute__((packed));

void idt_init();
#endif
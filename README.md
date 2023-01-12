# Multi-Threaded Kernel
### This project aims to implement a multithreaded kernel

## Prerequisities
A computer running Linux\
The QEMU emulator\
The NASM assembler\

## Installation notes on Ubuntu
QEMU:\
```sudo apt install qemu-system-x86```\
NASM:\
```sudo apt install nasm```\

## Useful commands
Generating a binary from an assembly file:\
```nasm -f bin ./boot.asm -o ./boot.bin```\
Disassembling a binary file:\
```qemu-system-x86_64 -hda ./boot.bin```\
Loading a binary into QEMU:\
```qemu-system-x86_64 -hda ./boot.bin```
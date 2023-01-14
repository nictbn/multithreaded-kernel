# Multi-Threaded Kernel
### This project aims to implement a multithreaded kernel

## Prerequisities
A computer running Linux\
The QEMU emulator\
The NASM assembler\
The make utility for automating the build process
The bless hexadecimal editor for viewing hexadecimal and binaty files

## Installation notes on Ubuntu
QEMU:\
```sudo apt install qemu-system-x86```\
NASM:\
```sudo apt install nasm```\
Make:\
```sudo apt install make```\
Bless:\
```sudo apt install bless```\

## Useful commands
Generating a binary from an assembly file:\
```nasm -f bin ./boot.asm -o ./boot.bin```\
Disassembling a binary file:\
```qemu-system-x86_64 -hda ./boot.bin```\
Loading a binary into QEMU:\
```qemu-system-x86_64 -hda ./boot.bin```
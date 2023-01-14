# Multi-Threaded Kernel
### This project aims to implement a multithreaded kernel

## Prerequisities
A computer running Linux\
The QEMU emulator\
The NASM assembler\
The make utility for automating the build process\
The bless hexadecimal editor for viewing hexadecimal and binary files\
The gdb debugger

## Installation notes on Ubuntu
QEMU:\
```sudo apt install qemu-system-x86```\
NASM:\
```sudo apt install nasm```\
Make:\
```sudo apt install make```\
Bless:\
```sudo apt install bless```\
gdb:\
```sudo apt install gdb```\
Please see the steps for creating your own cross compiler outlined below

## Useful commands
Generating a binary from an assembly file:\
```nasm -f bin ./boot.asm -o ./boot.bin```\
Disassembling a binary file:\
```qemu-system-x86_64 -hda ./boot.bin```\
Loading a binary into QEMU:\
```qemu-system-x86_64 -hda ./boot.bin```\
Debugging:\
```gdb```\
```target remote | qemu-system-x86_64 -hda ./boot.bin -S -gdb stdio```\

## Useful resources
[Protected mode](https://wiki.osdev.org/Protected_Mode)\
[Enabling the A20 Line](https://wiki.osdev.org/A20_Line)\
[Setting up a cross-compiler](https://wiki.osdev.org/GCC_Cross-Compiler)

## Steps for setting up your own cross compiler
1. install the dependencies outlined [here](https://wiki.osdev.org/GCC_Cross-Compiler#:~:text=CLooG%20(optional)-,Installing%20Dependencies,-%E2%86%93%20Dependency%20/%20OS%20%E2%86%92) in accordance with your OS
2. Extract binutils 2.35 from [here](https://ftp.gnu.org/gnu/binutils/binutils-2.35.tar.gz) into $HOME/src
3. Extract GCC version 10.2 from [here](https://ftp.lip6.fr/pub/gcc/releases/gcc-10.2.0/gcc-10.2.0.tar.gz) into $HOME/src
4. To install binutils open a new terminal and run the following commands:
```
export PREFIX="$HOME/opt/cross"
export TARGET=i686-elf
export PATH="$PREFIX/bin:$PATH"
cd $HOME/src
mkdir build-binutils
cd build-binutils
../binutils-2.35/configure --target=$TARGET --prefix="$PREFIX" --with-sysroot --disable-nls --disable-werror
make
make install
```
5. to install GCC open a new terminal and run the following commands:
```
export PREFIX="$HOME/opt/cross"
export TARGET=i686-elf
export PATH="$PREFIX/bin:$PATH"
cd $HOME/src
which -- $TARGET-as || echo $TARGET-as is not in the PATH
mkdir build-gcc
cd build-gcc
../gcc-10.2.0/configure --target=$TARGET --prefix="$PREFIX" --disable-nls --enable-languages=c,c++ --without-headers
make all-gcc
make all-target-libgcc
make install-gcc
make install-target-libgcc
```
This is a working example of Bare Bones tutorial from wiki.osdev.org

I made this repo because the Bare Bones article fucking sucks and is outdated.

## Features

This is a Multiboot-compliant i686 OS kernel.

- A lot of comments
- More simpler linker script
- Useful asm macros in macro.s
- C language usage
- `terminal.c` library for basic printing
- A function to convert an integer into hexadecimal string
- Run script

## Requirements

- Working cross-compiler `gcc` and `binutils` in `./cross-compiler` directory (`thisrepo/cross-compiler/bin/i686-elf-gcc` must exist) ([How to build a cross compiler](https://wiki.osdev.org/GCC_Cross-Compiler).)
- `qemu-system-x86` installed
- `grub` installed (for `grub-file` command)
- Additionally `xorriso` installed if you wish to make GRUB ISO image with your OS inside

# How to run

`cd` to this directory and `./run`

## Useful reference documentation

- [Up-to-date `ld` documentation](https://sourceware.org/binutils/docs/ld/index.html)
- [GNU `as` directives](https://sourceware.org/binutils/docs-2.41/as/Pseudo-Ops.html)
- [Multiboot Specification](https://www.gnu.org/software/grub/manual/multiboot/multiboot.html)
- [Refine Google searches](https://support.google.com/websearch/answer/2466433). Pesonally, I use quotes (`"this whole term matches exactly"`), `site:` and negation (`-"this term will be removed"`) a lot

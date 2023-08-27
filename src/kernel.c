#include <stdbool.h>
#include <stddef.h>

#include "terminal.c"

#if __linux__
	#error "Not using a cross-compiler"
#endif

#if !__i386__
	#error "Not using an ix86-elf compiler"
#endif

void kernel_main() 
{
	terminal_initialize();
	terminal_putString("Hello, world!!!!!\nhiii");
}

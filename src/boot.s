.intel_syntax noprefix

.include "src/macro.s"

.text
.global _start

multiboot_header:
	.align 4
	.long 0x1BADB002  # magic
	multiboot_flags = 0x00000000  # flags
	.long multiboot_flags
	.long -(0x1BADB002 + multiboot_flags)  # checksum

_start:
	# setting up stack
	mov esp, (stack + stack_size)

	call main

	print_int (stack + stack_size)

	# halt
	cli
	1:
		hlt
		jmp 1b

# stack
.bss
	.align 16
	stack_size = 0x4000  # 16 KiB
	.lcomm stack, stack_size

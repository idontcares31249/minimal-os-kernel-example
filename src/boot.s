.intel_syntax noprefix

# macros
	# prints character in terminal at index
	# ruins eax and ebx
	.macro print_char character=' , index=0, attr=0x07 /* light grey */
		mov ah, \attr
		mov al, \character
		mov ebx, \index
		mov word ptr 0xb8000[2 * ebx], ax
	.endm

	.macro clear_screen
		mov ecx, (80 * 24)
	1:
		print_char ' , ecx
		dec ecx
		jnz 1b
	.endm

	# prints hello
	.macro print_hello index=0
		print_char 'h, (\index + 0)
		print_char 'e, (\index + 1)
		print_char 'l, (\index + 2)
		print_char 'l, (\index + 3)
		print_char 'o, (\index + 4)
	.endm

	.macro _print_int_round value, index, round
		mov eax, \value
		shr eax, (\round * 4)
		and eax, 0x0000000f
		cmp eax, 10
		jge 1f
	# < 10
		add eax, '0
		jmp 2f
	# > 10
	1:
		add eax, ('A - 10)
	# end if
	2:
		print_char al, (\index + (7 - \round))
	.endm

	# converts dword to hex and prints
	.macro print_int value, index=0
		_print_int_round \value, \index, 0
		_print_int_round \value, \index, 1
		_print_int_round \value, \index, 2
		_print_int_round \value, \index, 3
		_print_int_round \value, \index, 4
		_print_int_round \value, \index, 5
		_print_int_round \value, \index, 6
		_print_int_round \value, \index, 7
	.endm
# /macros

.section .text
.global _start

_start:
	mov dword ptr [0xb8000], 0x07690748
	jmp entry

multiboot_header:
	.align 4
	.long 0x1BADB002  # magic
	multiboot_flags = 0x00000001  # flags
	.long multiboot_flags
	.long -(0x1BADB002 + multiboot_flags)  # checksum

entry:
	# setting up stack
	mov esp, (stack + stack_size)

	#clear_screen

	#print_int esp, (80 * 0)
	#push 0x1234cdef
	#pop ecx
	#print_int ecx, (80 * 1)

	# halt
	cli
	1:
		hlt
		jmp 1b

# stack
	.align 16
	stack_size = 0x4000
	.comm stack, stack_size

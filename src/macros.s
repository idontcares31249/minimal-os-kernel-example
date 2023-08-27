# collection of useful macros in case the stack hasn't been set up yet

.intel_syntax noprefix

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

/*
Basic linker script.
Kernel is loaded at 1M.
Sections are aligned at page size (4K) to not mix read-only, writable, executable memory
*/

OUTPUT_FORMAT(elf32-i386)
ENTRY(_start)

SECTIONS
{
	. = 1M;
	.text : ALIGN(4K) {
		*(.text)
	}
	.data : ALIGN(4K) {
		*(.data)
	}
	.bss : ALIGN(4K) {
		*(.bss)
	}
}

ENTRY(_start)
OUTPUT_FORMAT(elf32-i386)

SECTIONS
{
	. = 1M;

	.text BLOCK(4K) : {
		*(.multiboot)
		*(.text)
	}

	.data BLOCK(4K) : {
		*(.data)
	}

	.bss BLOCK(4K) : {
		*(COMMON)
		*(.bss)
	}
}

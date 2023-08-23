ENTRY(_start)
OUTPUT_FORMAT(elf32-i386)

SECTIONS
{
  . = 1M;

	.multiboot : {
		*(.multiboot)
	}

	# rest
	.text : {
		*(.text)
	}
	.rodata : {
		*(.rodata)
	}
	.data : {
		*(.data)
	}
	.bss : {
		*(COMMON)
		*(.bss)
	}
}

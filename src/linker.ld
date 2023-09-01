/*
Basic linker script.
. = 1M;    - means the kernel will be loaded in RAM at 1M. This is not required, but is a good practice I guess.
ALIGN(4K)    - means the sections will be aligned at page-sized (4K) boundaries, so that .text is put in a page with RX permissions and .data and .bss are in RW page. This is not required, but linker throws a warning otherwise. There is also BLOCKS(4K) in some other linker scripts but these are synonymous and ALIGN is newer.
Almost everything else is required.
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

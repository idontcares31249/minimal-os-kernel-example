#include <stddef.h>
#include <stdbool.h>

#include "terminal.c"
#include "util.c"

#if __linux__
	#error "Not using a cross-compiler"
#endif

#if !__i386__
	#error "Not using an ix86-elf compiler"
#endif

void drawRect(char ch, size_t col, size_t row, size_t width, size_t height, terminal_color fg, terminal_color bg)
{
	for (size_t y = row; y < row + height; y++)
	for (size_t x = col; x < col + width ; x++)
		terminal_putCharAt(ch, x, y, fg, bg);
}

void main() 
{
	terminal_initialize();

	// newline test
	terminal_putString("Hello, world!!!!!\nhiii\n");

	// color test
	for (int i = 0; i < 16; i++)
	{
		terminal_color clr = i;
		bool isLight = i >= 8;
		size_t
			col = i - isLight * 8,
			row = 3 + isLight * 1;
		terminal_putCharAt(' ', col, row, terminal_color_grey, clr);
		terminal_putCharAt('a', col + 9, row, clr, terminal_color_black);
	}

	// ascii test
	for (int i = 0; i < 0x100; i++)
	{
		terminal_putCharAt((char)i, i % 0x40, 6 + i / 0x40, terminal_color_grey, terminal_color_black);
	}

	// int_to_hex test
	char buffer[9] = { };
	int_to_hex(0x1234cdef, buffer);
	terminal_row = 11;
	terminal_putString(buffer);

	terminal_putString("\n\xb0\xb1\xb2");

	// lgbt test
	const size_t
		w = 18,
		x = 60,
		y = 18;
	const terminal_color
		grey = terminal_color_grey,
		red = terminal_color_light | terminal_color_red,
		orange = terminal_color_red | terminal_color_green,
		yellow = terminal_color_light | terminal_color_red | terminal_color_green,
		green = terminal_color_light | terminal_color_green,
		blue = terminal_color_light | terminal_color_blue,
		violet = terminal_color_light | terminal_color_red | terminal_color_blue;
	drawRect(' '   , x, y + 0, w, 1, grey, red     );
	drawRect('\xb0', x, y + 1, w, 1, yellow, orange);
	drawRect(' '   , x, y + 2, w, 1, grey, yellow  );
	drawRect(' '   , x, y + 3, w, 1, grey, green   );
	drawRect(' '   , x, y + 4, w, 1, grey, blue    );
	drawRect(' '   , x, y + 5, w, 1, grey, violet  );
}

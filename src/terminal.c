#pragma once

#include <stdint.h>
#include <stddef.h>

#include "util.c"

typedef uint8_t terminal_color;
// basic flags
#define terminal_color_blue      0b0001
#define terminal_color_green     0b0010
#define terminal_color_red       0b0100
#define terminal_color_light     0b1000
// use can OR these to get magenta, cyan, etc
// some more colors
#define terminal_color_black     0b0000
#define terminal_color_darkgrey  0b1000
#define terminal_color_grey      0b0111
#define terminal_color_white     0b1111

struct _terminal_cell_attrib
{
	terminal_color foreground : 4;
	terminal_color background : 4;
};

struct _terminal_cell
{
	uint8_t character;
	struct _terminal_cell_attrib attrib;
};

// just to ensure
static_assert(sizeof(struct _terminal_cell) == 2,
	"vga cell must be exactly 2 bytes long");

struct _terminal_cell _terminal_cell_new(char character, terminal_color fg, terminal_color bg)
{
	return (struct _terminal_cell){
		.character = (uint8_t)character,
		.attrib = (struct _terminal_cell_attrib){
			.foreground = fg,
			.background = bg
		}
	};
}

// by default
const size_t terminal_width = 80;
const size_t terminal_height = 25;

size_t terminal_column = 0;
size_t terminal_row = 0;
terminal_color terminal_foreground = terminal_color_grey;
terminal_color terminal_background = terminal_color_black;

// moves cursor based on given character
// increments cursor, or feeds line if '\n'
void _terminal_moveCursor(char control)
{
	if (control == '\n')
	{
		++terminal_row;
		terminal_column = 0;
	}
	else
	{
		++terminal_column;
	}

	if (terminal_column >= terminal_width)
	{
		++terminal_row;
		terminal_column = 0;
	}

	if (terminal_row >= terminal_height)
	{
		terminal_row = 0;
	}
}

void terminal_putCharAt(char ch, size_t col, size_t row, terminal_color fg, terminal_color bg)
{
	// vga buffer is at address 0xb8000
	struct _terminal_cell *const buffer = (struct _terminal_cell *)0xb8000;
	// constructing cell
	struct _terminal_cell cell = _terminal_cell_new(ch, fg, bg);
	// calculating index
	size_t inx = terminal_width * row + col;
	// writing to the buffer
	buffer[inx] = cell;
}

void terminal_putString(const char string[])
{
	for (size_t i = 0; string[i] != '\0'; i++)
	{
		char ch = string[i];
		if (ch != '\n')
			terminal_putCharAt(ch,
				terminal_column, terminal_row,
				terminal_foreground, terminal_background);
		_terminal_moveCursor(ch);
	}
}

void terminal_clear(terminal_color bg)
{
	for (size_t y = 0; y < terminal_height; y++)
	for (size_t x = 0; x < terminal_width ; x++)
		terminal_putCharAt(' ',
			x, y,
			terminal_color_grey, bg);
}

void terminal_initialize()
{
	terminal_clear(terminal_color_black);
	terminal_column = 0;
	terminal_foreground = terminal_color_grey;
	terminal_background = terminal_color_black;
}

// stuff to do next:
// - input
// - scrolling instead of wrapping the cursor around

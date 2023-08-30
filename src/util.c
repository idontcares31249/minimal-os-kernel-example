#pragma once

#define static_assert _Static_assert

// converts an int into hexadecimal string and puts it into buffer
// (which must have length of at least 8 chars)
void int_to_hex(int value, char buffer[])
{
	// (2 * sizeof(int)) as there are two hex digits in one byte
	for (int i = 0; i < 2 * sizeof(int); i++)
	{
		// get the value of the digit (0 to f)
		int b = value & 0xf;

		// convert to char
		char ch;
		if (b < 10)
			ch = b + '0';
		else
			ch = b - 10 + 'A';

		// put the char to buffer
		buffer[7 - i] = ch;

		// shift to next hex digit
		value >>= 4;
	}
}
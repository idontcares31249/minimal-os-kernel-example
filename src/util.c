#pragma once

void int_to_hex(int value, char buffer[])
{
	for (int i = 0; i < 8; i++)
	{
		int b = value & 0xf;

		char ch;
		if (b < 10)
			ch = b + '0';
		else
			ch = b - 10 + 'A';
		buffer[7 - i] = ch;

		value >>= 4;
	}
}
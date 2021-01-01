#include <genesis.h>

extern void aaa(short i, char* c);

// 40x28 tiles/chars on screen

void display(char* s)
{
	VDP_drawText(s, 0, 1);
	VDP_clearTextArea(0,0,20,14);
}

char lineBuffer[41] = { 0 };
short lineI = 0;
short lineY = 0;

void flushLine()
{
	if(lineI > 0)
	{
		if(lineI > 40)
		{
			lineI = 41;
		}
		lineBuffer[lineI] = 0;
		lineI = 0;
		VDP_clearText(0, lineY, 28);
		VDP_drawText(lineBuffer, 0, lineY);
	}
	++lineY;
	if(lineY >= 28)
	{
		lineY = 0;
	}
}

void putc(char c)
{
	if(lineI >= 40)
	{
		flushLine();
	}
	lineBuffer[lineI++] = c;
}

void puts(char* s)
{
	for(; *s != 0; ++s)
	{
		if(*s == '\n')
		{
			flushLine();
		}
		else
		{
			putc(*s);
		}
	}
}

void print(char* s)
{
	puts(s);
	flushLine();
}

int main()
{
	print("   //////////////////////////////////\n\
   /     ___         _____________  /\n\
   /    /   | ____  / ____<  / __ \\ /\n\
   /   / /| |/ __ \\/ /    / / /_/ / /\n\
   /  / ___ / /_/ / /___ / /\\__, /  /\n\
   / /_/  |_\\____/\\____//_//____/   /\n\
   /                                /\n\
   //////////////////////////////////\n");
	print("Welcome to Advent of Code 2019, to be\nattempted on the SEGA Mega Drive using\nC and 68k ASM!");

	while(1)
	{
		SYS_doVBlankProcess();
	}
	return (0);
}

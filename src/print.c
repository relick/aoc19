#include "print.h"
#include <genesis.h>

// 40x28 tiles/chars on screen
// use left column for line counter

void display(char const* s)
{
	VDP_drawText(s, 0, 1);
	VDP_clearTextArea(0,0,20,14);
}

char lineBuffer[41] = { '>' };
u16 lineI = 1;
u16 lineY = 0;
u16 prevLineY = 27;

void flushLine()
{
	if(lineI > 0)
	{
		if(lineI > 40)
		{
			lineI = 41;
		}
		lineBuffer[lineI] = 0;
		lineI = 1;
		VDP_clearText(0, prevLineY, 1);
		VDP_clearText(0, lineY, 40);
		VDP_drawText(lineBuffer, 0, lineY);
	}
	prevLineY = lineY++;
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

void puts(char const* s)
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

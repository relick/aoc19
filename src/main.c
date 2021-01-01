#include <genesis.h>

#include "print.h"
#include "inputs.h"
#include "days.h"

extern void aaa(u16 i, char const* s);

int main()
{
	print("  //////////////////////////////////\n\
  /     ___         _____________  /\n\
  /    /   | ____  / ____<  / __ \\ /\n\
  /   / /| |/ __ \\/ /    / / /_/ / /\n\
  /  / ___ / /_/ / /___ / /\\__, /  /\n\
  / /_/  |_\\____/\\____//_//____/   /\n\
  /                                /\n\
  //////////////////////////////////\n");
	print("Welcome to Advent of Code 2019, to be\nattempted on the SEGA Mega Drive using\nC and 68k ASM!\n");

	print("Running...");
	
	SYS_doVBlankProcess();

	day1_c();

	while(1)
	{
		SYS_doVBlankProcess();
	}
	return (0);
}

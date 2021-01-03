#include <genesis.h>
#include "days.h"
#include "inputs.h"
#include "print.h"
#include "intcode.h"

void day2_c()
{
	print("Day 2 (C):");
	u16 const length = intcodeLength(input02) * sizeof(u32);
	u16 const numBytes = length * sizeof(u32);
	u32* program = intcodeParse(input02, numBytes);
	u32* testProgram = MEM_alloc(numBytes);
	memcpy(testProgram, program, numBytes);
	testProgram[1] = 12;
	testProgram[2] = 2;
	intcodeRun(testProgram, length, NULL);
	print("\nPart 1:");
	printInt(testProgram[0]);
	
	print("\nRunning part 2...");
	for(u16 x = 0; x <= 99; ++x)
	{
		for(u16 y = 0; y <= 99; ++y)
		{
			memcpy(testProgram, program, numBytes);
			testProgram[1] = x;
			testProgram[2] = y;
			intcodeRun(testProgram, length, NULL);
			if(testProgram[0] == 19690720)
			{
				print("...Done!");
				print("\nPart 2:");
				printInt((100 * x) + y);
				goto breakout;
			}
		}
	}
	breakout:;
	MEM_free(testProgram);
	MEM_free(program);
}
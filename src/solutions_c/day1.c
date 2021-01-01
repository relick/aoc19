#include "days.h"

#include <genesis.h>
#include "inputs.h"
#include "print.h"

void day1_c()
{
	print("Day 1 (C):");

	s32 n = 0;
	u8 const* c = input01;
	s32 fuelSumPart1 = 0;
	s32 fuelSumPart2 = 0;
	for(; *c != 0; ++c)
	{
		if(*c == '\n')
		{
			s32 extraFuel = n;
			{
				extraFuel /= 3;
				extraFuel -= 2;
				if(extraFuel < 0)
				{
					extraFuel = 0;
				}
				fuelSumPart1 += extraFuel;
				fuelSumPart2 += extraFuel;
			}
			while (extraFuel > 0)
			{
				extraFuel /= 3;
				extraFuel -= 2;
				if(extraFuel < 0)
				{
					extraFuel = 0;
				}
				fuelSumPart2 += extraFuel;
			}
			n = 0;
		}
		else
		{
			n *= 10;
			n += *c - '0';
		}
	}

	print("\nPart 1:");
	printInt(fuelSumPart1);
	print("\nPart 2:");
	printInt(fuelSumPart2);
}
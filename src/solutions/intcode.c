#include <genesis.h>
#include "intcode.h"
#include "days.h"
#include "inputs.h"
#include "print.h"

#define DEBUG 0

#if DEBUG
void checkBounds32(u32* _a, u16 _len)
{
	if(*_a >= _len)
	{
		print("beyond length");
		*_a = 0;
	}
}

void checkBounds16(u16* _a, u16 _len)
{
	if(*_a >= _len)
	{
		print("beyond length");
		*_a = 0;
	}
}
#else
void checkBounds32(u32* _a, u16 _len) {}
void checkBounds16(u16* _a, u16 _len) {}
#endif

void intcodeRun(u32* _p, u16 _length, u32* _input)
{
	u16 ip = 0;
	while(ip < _length)
	{
		switch(_p[ip])
		{
			case 1:
			{
				u32 a = _p[++ip];
				checkBounds32(&a, _length);
				a = _p[a];
				u32 b = _p[++ip];
				checkBounds32(&b, _length);
				b = _p[b];
				u16 dest = _p[++ip];
				checkBounds16(&dest, _length);
				_p[dest] = a + b;
				++ip;
				break;
			}
			case 2:
			{
				u32 a = _p[++ip];
				checkBounds32(&a, _length);
				a = _p[a];
				u32 b = _p[++ip];
				checkBounds32(&b, _length);
				b = _p[b];
				u16 dest = _p[++ip];
				checkBounds16(&dest, _length);
				_p[dest] = a * b;
				++ip;
				break;
			}
			case 3:
			{
				// take input and put at dest
				u16 dest = _p[++ip];
				checkBounds16(&dest, _length);
				_p[dest] = *(_input++);
				++ip;
				break;
			}
			case 4:
			{
				// output what is at src
				u16 src = _p[++ip];
				checkBounds16(&src, _length);
				printInt(_p[src]);
				++ip;
				break;
			}
			case 99:
			{
				return;
			}
			default:
			{
				print("invalid instruction");
				printInt(_p[ip]);
				return;
			}
		}
	}

	print("didn't hit 99 to halt");
}
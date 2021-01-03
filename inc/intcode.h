#pragma once

#include <genesis.h>

extern u16 intcodeLength(u8 const* _input);
extern u32* intcodeParse(u8 const* _input, u16 _length);
void intcodeRun(u32* _program, u16 _length, u32* _input);
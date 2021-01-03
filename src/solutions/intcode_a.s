#include "asm_mac.i"

//; extern u16 intcodeLength(u8 const* _input);
func intcodeLength
	movea.l	4(%sp),%a0 //; put input addr in a0
	
	//; scroll input and count commas
	moveq.l	#0,%d0 //; length

	move.b	(%a0)+,%d1
	jeq		finishInputLen

forEachCharLen:
	cmp.b	#',',%d1
	jne		nextCharLen

	add.w	#1,%d0
nextCharLen:
	move.b	(%a0)+,%d1
	jne		forEachCharLen

	add.w	#1,%d0 //; final item that doesn't have comma after

finishInputLen:
	rts

//; extern u32* intcodeParse(u8 const* _input, u16 _length);
func intcodeParse
	
	//; allocate memory for the program
	move.l	8(%sp),%d0
	mulu.w	#4,%d0
	move.l	%d0,-(%sp)
	jbsr	MEM_alloc
	addq.l	#4,%sp

	movea.l	4(%sp),%a0 //; put input addr in a0
	movea.l	%d0,%a1 //; put alloc in a1

	//; save registers
	movem.l	%a2/%d2,-(%sp)

	movea.l	%a1,%a2 //; update %a1 with each num
	
	//; process input into program.
	moveq.l	#0,%d2 //; curNum

	move.b	(%a0)+,%d1
	jeq		finishInput
	

forEachChar:
	cmp.b	#',',%d1
	jne		addDigit

	move.l	%d2,(%a1)+
	moveq.l	#0,%d2
	jra		nextChar

addDigit:
	mulu.w	#10,%d2
	and.w	#255,%d1
	add.w	%d1,%d2
	sub.w	#'0',%d2
nextChar:
	move.b	(%a0)+,%d1
	jne		forEachChar

finishInput:
	move.l	%d2,(%a1)+ //; final entry
	move.l	%a2,%d0

	//; restore registers
	movem.l	(%sp)+,%a2/%d2
	rts
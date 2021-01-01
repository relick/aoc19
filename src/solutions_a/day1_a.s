#include "asm_mac.i"

	.globl	__divsi3

.dayText:
	.string "Day 1 (ASM):"

.part1:
	.string "\nPart 1:"

.part2:
	.string "\nPart 2:"

//; extern void day1_a();
func day1_a
	//; save registers
	movem.l	%a2/%d2-%d5,-(%sp)

	//; print today
	pea		.dayText
	jbsr	print
	addq.l	#4,%sp

	lea		input01,%a0

	moveq.l	#0,%d3 //; part 1
	moveq.l	#0,%d4 //; part 2
	moveq.l	#0,%d5 //; 0 = add to both, 1 = part 2 only
	moveq.l	#0,%d2 //; curNum
	
	move.b	(%a0)+,%d1
	tst.b	%d1
	jeq		finish

forEachChar:
	cmp.b	#'\n',%d1
	jne		addDigit

processItem:
	//; div only works on words... gotta use software alt
	//;divu.w	#3,%d2
	//;ext.l	%d2
	pea		3.w
	move.l	%d2,-(%sp)
	jbsr	__divsi3
	addq.l	#8,%sp
	move.l	%d0,%d2
	subq.l	#2,%d2
	cmp.l	#0,%d2
	jge		addToSum
	moveq.l	#0,%d2 //; clip d2 to 0
addToSum:
	tst.b	%d5
	jne		addToPart2Sum
	add.l	%d2,%d3
	add.b	#1,%d5
addToPart2Sum:
	add.l	%d2,%d4
	tst.l	%d2
	jne		processItem
	moveq.l	#0,%d5
	jra		nextChar

addDigit:
	//; multiply a u32 by 10
	//; mulu is only u16 max.
	//; mulu.l	#10,%d2
	move.l	%d2,%d0 //; d0 = 1x
	add.l	%d2,%d0 //; d0 = 2x
	add.l	%d0,%d0 //; d0 = 4x
	add.l	%d0,%d2 //; d2 = 5x
	add.l	%d2,%d2 //; d2 = 10x
	//; end x10
	and.l	#255,%d1
	add.l	%d1,%d2
	sub.l	#'0',%d2

nextChar:
	move.b	(%a0)+,%d1
	jne		forEachChar

finish:
	pea		.part1
	jbsr	print
	addq	#4,%sp

	move.l	%d3,-(%sp)
	jbsr	printInt
	addq	#4,%sp
	
	pea		.part2
	jbsr	print
	addq	#4,%sp

	move.l	%d4,-(%sp)
	jbsr	printInt
	addq	#4,%sp

	movem.l	(%sp)+,%a2/%d2-%d5
	rts
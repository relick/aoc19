	.text
	.align	2
	.globl	aaa
aaa:
	//; top of stack is jsr address, as a long
	//; parameters are then in-order, as longs.
	//; to call a function, push params in reverse order then pop with lea after.
	//; d0-d1 are scratch, a0-a1 are scratch, others must be saved if the function is going to use them and undone before rts
	move.l	4(%sp),-(%sp)
	pea		0.w //; [SP] <- [SP] - 4 [M(SP)] <- <ea>
	move.l	16(%sp),-(%sp)
	jsr		VDP_drawText
	lea		(12,%sp),%sp

	//; allocate string
	pea		16.w
	jsr		MEM_alloc
	addq	#4,%sp
	//; save a2
	move.l	%a2,-(%sp)
	//; str ptr into a0
	movea.l	%d0,%a2
	moveq	#6,%d1
	//; set characters
fillLoop:
	move.b	#'A',(%a2)+
	dbf		%d1,fillLoop
	//; call display
	move.b	#0,(%a2)
	suba.w	#6,%a2
	move.l	%a2,-(%sp)
	jsr		display
	addq	#4,%sp
	//; free address
	move.l	%a2,-(%sp)
	jsr		MEM_free
	addq	#4,%sp
	//; unsave a2
	movea.l	(%sp)+,%a2

	nop
	rts
	.size	aaa, .-aaa

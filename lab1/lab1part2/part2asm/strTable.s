	.file	"part1-strTable.c"
	.text
	.align	2
	.global	strTable
	.type	strTable, %function
strTable:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	stmfd	sp!, {r4, r5, r6}
	subs	r4, r3, #1
	blt	.L11
.L9:
	ldrb	r6, [r1, r4]	@ zero_extendqisi2
	mov ip, r6
.L7:
	sub	ip, ip, #23
	cmp	ip, #22
	bgt	.L7
.L13:
	cmp	ip, r2
	bgt	.L4
	ldrb	r5, [r0, ip]	@ zero_extendqisi2
	cmp	r5, r6
	strneb 	r5, r6
.L4:
	subs	r4, r4, #1
	bge	.L9
.L11:	
	ldmfd	sp!, {r4, r5, r6}
	mov pc, lr
	.size	strTable, .-strTable
	.ident	"GCC: (GNU) 3.4.5"

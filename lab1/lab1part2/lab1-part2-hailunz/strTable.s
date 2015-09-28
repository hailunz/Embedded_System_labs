	@ ID: hailunz	
	.file	"part1-strTable.c"
	.text
	.align	2
	.global	strTable
	.type	strTable, %function
strTable:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	stmfd	sp!, {r4, r5}
	subs	r4, r3, #1
	blt	.L11
.L9:
	ldrb	r5, [r1], #1	@ zero_extendqisi2
	sub	ip, r5, #23
	cmp	ip, #22
.L7:
	subgt	ip, ip, #23
	cmp	ip, #22
	subgt	ip, ip, #23
	cmp	ip, #22
	bgt	.L7
.L13:
	cmp	ip, r2
	strleb	r5, [r0, ip]
.L4:
	subs	r4, r4, #1	
	bge	.L9
.L11:
	ldmfd	sp!, {r4, r5}
	mov pc, lr
	.size	strTable, .-strTable
	.ident	"GCC: (GNU) 3.4.5"

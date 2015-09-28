@ write.S: write sycall wrapper
@
@ Authors: Hailun Zhu <hailunz@andrew.cmu.edu>
@ Date:    02 Oct, 2014
#include <bits/swi.h>
#include <bits/errno.h>

	.file	"write.S"
	.text
	.align 2
	.global	write
write:
	swi WRITE_SWI
	cmp r0, #0
	bge .L2
.L1:	
	neg r1, r0
	ldr r0, =errno
	str r1,[r0]
	mov r0, #-1
.L2:
	mov pc, lr

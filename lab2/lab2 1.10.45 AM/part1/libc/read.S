@ read.S: read sycall wrapper
@
@ Authors: Hailun Zhu <hailunz@andrew.cmu.edu>
@ Date:    03 Oct, 2014
#include <bits/swi.h>
#include <bits/errno.h>

	.file	"read.S"
	.text

	.global	read
read:
	swi READ_SWI
	cmp r0, #0
	bge .L2
.L1:
	neg r1,r0
	ldr r0, =errno
	str r1, [r0]
	mov r0,#-1 

.L2:
	mov pc, lr
	

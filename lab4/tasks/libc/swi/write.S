/** @file write.S
 *
 * @brief write sycall wrapper
 *
 * Author: Hailun Zhu <hailunz@andrew.cmu.edu>
 * 	   Xinkai Wang <xinkaiw@andrew.cmu.edu>
 * Date 11/1/2014
 */

#include <asm.h>
#include <bits/swi.h>
#include <bits/errno.h>

	.file "write.S"

FUNC(write)
	@ Add code here.  Put your names at the top.
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

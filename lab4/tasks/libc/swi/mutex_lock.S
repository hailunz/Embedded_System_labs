/** @file time.S
 *
 * @brief time sycall wrapper
 *
 * Author: Hailun Zhu <hailunz@andrew.cmu.edu>
 *	   Xinkai Wang <xinkaiw@andrew.cmu.edu>
 * Date 11/23/2014
 */

#include <asm.h>
#include <bits/swi.h>
#include <bits/errno.h>

	.file "mutex_lock.S"

FUNC(mutex_lock)
	@ Add code here.  Put your name at the top.
	swi MUTEX_LOCK
	cmp r0, #0
	bge .L2
.L1:
	neg r1,r0
	ldr r0, =errno
	str r1, [r0]
	mov r0,#-1 

.L2:
	mov pc, lr

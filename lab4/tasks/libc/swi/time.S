/** @file time.S
 *
 * @brief time sycall wrapper
 *
 * Author: Hailun Zhu <hailunz@andrew.cmu.edu>
 * 	   Xinkai Wang <xinkaiw@andrew.cmu.edu>
 * Date 11/1/2014
 */

#include <asm.h>
#include <bits/swi.h>
#include <bits/errno.h>

	.file "time.S"

FUNC(time)
	@ Add code here.  Put your name at the top.
	swi TIME_SWI
	mov pc, lr

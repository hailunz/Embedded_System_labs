/** @file sleep.S
 *
 * @brief sleep sycall wrapper
 *
 * Author: Hailun Zhu <hailunz@andrew.cmu.edu>
 *	   Xinkai Wang <xinkaiw@andrew.cmu.edu>
 * Date 11/23/2014
 */

#include <asm.h>
#include <bits/swi.h>
#include <bits/errno.h>
	.file "sleep.S"

FUNC(sleep)
	@ Add code here.  Put your names at the top.
	swi SLEEP_SWI
	mov pc, lr

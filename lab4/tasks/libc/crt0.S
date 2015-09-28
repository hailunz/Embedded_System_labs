/** @file crt0.S
 *
 * @brief Execution startup routine
 *
 * Author: Hailun Zhu <hailunz@andrew.cmu.edu>
 * 	   Xinkai Wang <xinkaiw@andrew.cmu.edu>
 * Date 11/1/2014
 */

#include <asm.h>

	.file "crt0.S"

FUNC(_start)
	@ needs code.  Put your names at the top.
	ldr r0,[sp], #4
	mov r1, sp
	bl main


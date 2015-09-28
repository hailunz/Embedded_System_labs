@ exit.S: exit sycall wrapper
@
@ Authors: Hailun Zhu <hailunz@andrew.cmu.edu>
@ Date:    03 OCT, 2014

#include <bits/swi.h>
	.file	"exit.S"
	.text
	.align 2
	.global	exit
exit:
	swi EXIT_SWI

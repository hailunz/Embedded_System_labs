@ crt0.S: Execution startup routine
@
@ Authors: Hailun Zhu <hailunz@andrew.cmu.edu>
@ Date:    03 Oct, 2014

	.file	"crt0.S"
	.text

	.global	_start
_start:
	ldr r0,[sp], #4
	mov r1, sp
	bl main
	b  exit
	

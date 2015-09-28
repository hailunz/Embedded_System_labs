@ hello.S: Hello world! in assembly
@
@ Authors: Hailun Zhu <hailunz@andrew.cmu.edu>
@ Date:    02 Oct, 2014

#include <bits/fileno.h>
#include <bits/swi.h>

	.file	"hello.S"
	.text

	.global	_start
_start:

	mov r0, #STDOUT_FILENO
	ldr r1, =hello_str
	mov r2, #hello_size
	swi WRITE_SWI 
	mov r0, #0
	swi EXIT_SWI 

	.section	.rodata
hello_str:
	.ascii	"Hello world!\n"
	.set	hello_size, .-hello_str

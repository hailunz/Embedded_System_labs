@ IRQ_Handler.S: irq_handler startup routine
@ Author : Hailun Zhu <hailunz@andrew.cmu.edu>
@ time	 : 11/1/2014

	.file "IRQ_Handler.S"
	.text
	.align 2
	.extern irq_Handler
	.global IRQ_Handler

IRQ_Handler:
	stmfd	sp!, {r0-r12, lr} 	@ store user's gp registers
	mov 	r1, sp              	@ pointer to parameters on stack
	bl	irq_Handler           @ goto handler
	add	sp, sp, #4              @ get return value
	ldmfd	sp!, {r1-r12, lr} 	@ unstack user's registers
	movs	pc, lr              	@ return from handler

/*
 * S_Handler.S: swi_handler startup routine
 * Author: Hailun Zhu <hailunz@andrew.cmu.edu>
 *	   Xinkai Wang <xinkaiw@andrew.cmu.edu>
 * Date 11/23/2014
 */

	.file "S_Handler.S"
	.text
	.align 2
	.extern C_SWI_Handler
	.global S_Handler

S_Handler:
	
	/* Recover user registers and save */
	stmfd   sp, {sp, lr}^
	add     sp, sp, #-8	
	
	/* leave room on stack for SPSR */
	sub	sp, sp, #4              
	stmfd	sp!, {r0-r3, r8, ip, lr} 
	mrs	r2, spsr               
	str	r2, [sp, #28]           
	
	mrs	r2, cpsr
	bic	r2, r2, #0x80
	msr 	cpsr, r2
	
	/* restore r8 */
	ldr 	ip,=global_data
	ldr 	r8,[ip]
	
	/* extract swi number and go to swi handler */
	mov 	r1, sp              	
	ldr	r0, [lr, #-4]           
	bic	r0,r0,#0xff000000       
	bl	C_SWI_Handler          

	/* Restore registers.  Also restore CPSR. */
	ldr	r2, [sp, #28] 	
	msr	spsr, r2                
	add	sp, sp, #4              
	ldmfd	sp!, {r1-r3, r8, ip, lr} 	
	add	sp, sp, #4             

	ldmfd   sp, {sp, lr}^
	add     sp, sp, #8

	movs	pc, lr              	

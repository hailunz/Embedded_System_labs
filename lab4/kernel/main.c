/** @file main.c
 *
 * @brief kernel main
 *
 * Author: Hailun Zhu <hailunz@andrew.cmu.edu>
 *	   Xinkai Wang <xinkaiw@andrew.cmu.edu>
 * Date 11/23/2014
 */
 
#include <kernel.h>
#include <task.h>
#include <sched.h>
#include <device.h>
#include <assert.h>
#include <lock.h>

#include <exports.h>

#include <arm/psr.h>
#include <arm/exception.h>
#include <arm/interrupt.h>
#include <arm/timer.h>
#include <arm/reg.h>

#include <bits/fileno.h>
#include <bits/errno.h>


uint32_t global_data;

#define INS_ERROR 0x0badc0de
#define SYSCALLS 0x08
#define IRQ_NUM 0x18

extern void S_Handler();
extern void IRQ_Handler();
extern int switch_mode(int argc, char *argv[]);

size_t savesp;

volatile unsigned long global_time;
size_t install_handler(size_t *storeUboot,size_t num);
void restore_handler(size_t handler_addrs, size_t *storeUboot);


int kmain(int argc __attribute__((unused)), char** argv  __attribute__((unused)), uint32_t table)
{

	app_startup();
	global_data = table;
	/* add your code up to assert statement */
	int status=0; 
    	size_t storeSYS[2], handler_address_sys;
	size_t storeIRQ[2], handler_address_IRQ;
	savesp=0;
	global_time=0;
	
	// install syscalls handler
    	handler_address_sys= install_handler(storeSYS,SYSCALLS);
	if (handler_address_sys == INS_ERROR )
       		return INS_ERROR;
    
	// install IRQ handler
   	handler_address_IRQ= install_handler(storeIRQ,IRQ_NUM);
	if (handler_address_IRQ == INS_ERROR )
       		return INS_ERROR;
	init_timer();
	mutex_init();
    	// switch to user mode
    	status=switch_mode(argc, argv);
		
	assert(0);        /* should never get here */
}


void init_timer(void){
	// set timer

	/* Set up interrupt controller */
	reg_set(INT_ICMR_ADDR, (1 << INT_OSTMR_0));  // set OSTMR0 bit in ICMR to 1 to unmask OSTMR0
	reg_clear(INT_ICLR_ADDR, (1 << INT_OSTMR_0));  // set OSTMR0 bit in ICLR to 0, handle Timer0 with IRQ

	/* Timer setup */
	reg_write(OSTMR_OIER_ADDR, 0); // mask all interrup at first
	reg_set(OSTMR_OIER_ADDR, OSTMR_OIER_E0); // enable interrupt of timer 0
	reg_write(OSTMR_OSMR_ADDR(0), 32500); // 10 ms after 32500 clock cycles
	reg_write(OSTMR_OSCR_ADDR, 0);
	reg_write(OSTMR_OSSR_ADDR, 0);
}

// install my handler
size_t install_handler(size_t *storeUboot, size_t num){
    size_t *addr= (size_t *)num;
    size_t instruction = *(addr);
    size_t signs = (instruction >> 23) &1;
    size_t offset;
    size_t addr_in_vec;	
    size_t handler_addr;
    size_t *handler_pointer;
    size_t pc=num+0x08;
	
    // check LDR
    if ((instruction & 0xfffff000) != 0xe59ff000){
        puts("Unrecognized instruction\n");
        return INS_ERROR;
    }
    
    offset = instruction & 0xfff;
	
    // get address
    addr_in_vec = (signs==1)? (offset+pc):(pc-offset);

    handler_addr=*((size_t *)addr_in_vec);
    handler_pointer=(size_t *) handler_addr;
    // save the original handler
    storeUboot[0]= *  handler_pointer;
    storeUboot[1]= *  (handler_pointer+1);
    
    // set my handler
    // ldr pc, [pc, #-4]
    *  handler_pointer = 0xe51ff004;
	switch (num){    
		case SYSCALLS:
			* ( handler_pointer + 1) = (size_t) &S_Handler;
			break;
		case IRQ_NUM:
			* ( handler_pointer + 1) = (size_t) &IRQ_Handler;
			break;
}
    return handler_addr;
}

// restore the Uboot handler, do not need this function in this lab.
/*
void restore_handler(size_t handler_addrs, size_t *storeUboot){
    size_t * handler_pointer=(size_t *) handler_addrs;
    * handler_pointer = storeUboot[0];
    * (handler_pointer+1) = storeUboot[1];
}
*/

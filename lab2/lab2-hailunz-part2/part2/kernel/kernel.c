/*
 * kernel.c: Kernel main (entry) function
 *
 * Author: Hailun Zhu <hailunz@andrew.cmu.edu>
 *
 * Date:   10/14/2014
 */

#include <exports.h>
#include <bits/fileno.h>
#include <bits/errno.h>

#define INS_ERROR 0x0badc0de
extern void S_Handler();
extern int switch_mode(int argc, char *argv[]);
extern void exit(int status);

size_t savesp;
size_t install_handler(size_t *storeUboot);
void restore_handler(size_t handler_addrs, size_t *storeUboot);


int main(int argc, char *argv[]) {
   	int status=0; 
    	size_t storeOld[2], handler_address;
	savesp=0;
    
    // install my handler
    	handler_address= install_handler(storeOld);
	if (handler_address == INS_ERROR )
       		return INS_ERROR;
    
    // check the arguments
    // printf("kernel:argc:%d,argv:%s,%s,%s\n",argc,argv[0],argv[1],argv[2]) ;
 	
    // switch to user mode
    status=switch_mode(argc, argv);
    //printf("switch over:%d\n",status);
   	
    // restore original handler
    restore_handler(handler_address,storeOld);
    //puts("retore over!\n");
    
    return status;

}


// install my handler
size_t install_handler(size_t *storeUboot){
    size_t *addr= (size_t *)0x08;
    size_t instruction = *(addr);
    size_t signs = (instruction >> 23) &1;
    size_t offset;
    size_t addr_in_vec;	
    size_t handler_addr;
	
    // check LDR
    if ((instruction & 0xfffff000) != 0xe59ff000){
        puts("Unrecognized instruction\n");
        return INS_ERROR;
    }
    
    offset = instruction & 0xfff;
	
    // get address
    addr_in_vec = (signs==1)? (offset+0x10):(0x10-offset);
	//printf("addr_in_vec:%x\n",addr_in_vec);

    handler_addr=*((size_t *)addr_in_vec);
    
	//printf("handler:%x\n",handler_addr);

    // save the original handler
    storeUboot[0]= * ((size_t *) handler_addr);
    storeUboot[1]= * ((size_t *) (handler_addr+4));
    
    // set my handler
    // ldr pc, [pc, #-4]
    * ((size_t *) handler_addr) = 0xe51ff004;
    * ((size_t *) (handler_addr + 4)) = (size_t) &S_Handler;
    
    return handler_addr;
}

// restore the Uboot handler
void restore_handler(size_t handler_addrs, size_t *storeUboot){
    
    * ((size_t *) handler_addrs) = storeUboot[0];
    * ((size_t *) (handler_addrs + 4)) = storeUboot[1];

}








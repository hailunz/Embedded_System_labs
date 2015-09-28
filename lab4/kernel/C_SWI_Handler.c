/*
 * SWI handler
 * Author: Hailun Zhu <hailunz@andrew.cmu.edu>
 *	   Xinkai Wang <xinkaiw@andrew.cmu.edu>
 * Date 11/23/2014
 */
#include <exports.h>
#include <bits/swi.h>
#include <syscall.h>
#include <lock.h>

void C_SWI_Handler(unsigned swi_num, unsigned *regs){
    unsigned *value;
    value=regs;
    switch (swi_num) {
            case READ_SWI:
               *value= read_syscall(regs[0],(void *)regs[1],regs[2]);
                break;
            case WRITE_SWI:
                *value=write_syscall(regs[0],(void *)regs[1],regs[2]);
                break;
            case TIME_SWI:
                *value=time_syscall();
		break;
            case SLEEP_SWI:
                sleep_syscall(regs[0]);
		break;
            case CREATE_SWI:
                task_create((task_t *)regs[0],regs[1]);
		break;
            case MUTEX_CREATE:
                *value=mutex_create();
		break;
            case MUTEX_LOCK:
                *value=mutex_lock(regs[0]);
		break;
            case MUTEX_UNLOCK:
                *value=mutex_unlock(regs[0]);
		break;
            case EVENT_WAIT:
                event_wait(regs[0]);
		break;
            default:
		
                invalid_syscall(swi_num);
	} /* end switch */
    return;
}


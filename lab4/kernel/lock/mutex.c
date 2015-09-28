/**
 * @file mutex.c
 *
 * @brief Implements mutices.
 *
 * Author: Hailun Zhu <hailunz@andrew.cmu.edu>
 *	   Xinkai Wang <xinkaiw@andrew.cmu.edu>
 * Date 11/23/2014
 */

//#define DEBUG_MUTEX

#include <lock.h>
#include <task.h>
#include <sched.h>
#include <bits/errno.h>
#include <arm/psr.h>
#include <arm/exception.h>
//#ifdef DEBUG_MUTEX
#include <exports.h> // temp
//#endif

#define NULL 0

mutex_t gtMutex[OS_NUM_MUTEX];
int mutex_num = 0;
void mutex_release(){
	int i=0;
	for (i=0; i<OS_NUM_MUTEX; i++){
		gtMutex[i].pHolding_Tcb = NULL;
        	gtMutex[i].bLock = FALSE;
        	gtMutex[i].pSleep_queue = NULL;
	}
}
void mutex_init()
{
	int i = 0;
	for (i = 0; i < OS_NUM_MUTEX; i++) {
	        gtMutex[i].bAvailable = TRUE;
        	gtMutex[i].pHolding_Tcb = NULL;
        	gtMutex[i].bLock = FALSE;
        	gtMutex[i].pSleep_queue = NULL;
	}
	mutex_num = 0;
}

int mutex_create(void)
{
	disable_interrupts();

	if (mutex_num >= OS_NUM_MUTEX) {
		enable_interrupts();
		return -ENOMEM;
	}

	if (gtMutex[mutex_num].bAvailable == TRUE) {
		gtMutex[mutex_num].bAvailable = FALSE;
		mutex_num++;
	}
	enable_interrupts();
	return mutex_num - 1;
}

int mutex_lock(int mutex  __attribute__((unused)))
{
	disable_interrupts();

	mutex_t *cur_mutex = &gtMutex[mutex];

	// if the given mutex number is invalid
	if (mutex < 0 || mutex >= OS_NUM_MUTEX || cur_mutex->bAvailable == TRUE) {
		enable_interrupts();
		return -EINVAL;
	}

	tcb_t *cur_tcb = get_cur_tcb();
	
	// if current task hold the lock
	if (cur_mutex->pHolding_Tcb == cur_tcb) {
		// printf("deadlock!\n");
		enable_interrupts();
		return -EDEADLOCK;
	}

	// if current mutex is acquired by other task
	if (cur_mutex->bLock == TRUE) {
		tcb_t * previous_tcb = cur_mutex->pSleep_queue;
		tcb_t * next_tcb ;
		if (previous_tcb == NULL){
			cur_mutex->pSleep_queue = cur_tcb;
			cur_tcb->sleep_queue = NULL;		
		}
		next_tcb= previous_tcb->sleep_queue;
		while (next_tcb != NULL){
			previous_tcb = next_tcb;
			next_tcb = previous_tcb->sleep_queue;		
		}
		
		previous_tcb->sleep_queue = cur_tcb;
		cur_tcb->sleep_queue = NULL;

		dispatch_sleep();
	}

	cur_tcb->holds_lock++;
	cur_mutex->bLock = TRUE;
	cur_mutex->pHolding_Tcb = cur_tcb;
	
	enable_interrupts();
	return 0;
}

int mutex_unlock(int mutex  __attribute__((unused)))
{
	disable_interrupts();

	mutex_t *cur_mutex = &gtMutex[mutex];

	// if the given mutex identifier is invalid
	if (mutex < 0 || mutex >= OS_NUM_MUTEX || cur_mutex->bAvailable == TRUE) {
		enable_interrupts();
		return -EINVAL;
	}

	tcb_t *cur_tcb = get_cur_tcb();

	// if current task doesn't hold the lock
	if (cur_mutex->pHolding_Tcb != cur_tcb) {
		enable_interrupts();
		return -EPERM;
	}

	cur_mutex->bLock = FALSE;
	tcb_t *next_tcb = NULL;
    
	if (cur_mutex->pSleep_queue != NULL) {
	        next_tcb = cur_mutex->pSleep_queue;
	        cur_mutex->pSleep_queue = next_tcb->sleep_queue;
	        next_tcb->sleep_queue = NULL;
        
	        runqueue_add(next_tcb, next_tcb->cur_prio);
	}
    
    	cur_tcb->holds_lock--;
	cur_mutex->pHolding_Tcb = next_tcb;

	// if highest task is bigger than cur_tcb
	dispatch_save();
	
	enable_interrupts();
	return 0;
}


/**
 * @file device.c
 *
 * Author: Hailun Zhu <hailunz@andrew.cmu.edu>
 *	   Xinkai Wang <xinkaiw@andrew.cmu.edu>
 * Date 11/23/2014
 */

#include <types.h>
#include <assert.h>

#include <task.h>
#include <sched.h>
#include <device.h>
#include <arm/reg.h>
#include <arm/psr.h>
#include <arm/exception.h>
#include <exports.h>

#define NULL 0
extern volatile unsigned long global_time;

/**
 * @brief Fake device maintainence structure.
 * Since our tasks are periodic, we can represent 
 * tasks with logical devices. 
 * These logical devices should be signalled periodically 
 * so that you can instantiate a new job every time period.
 * Devices are signaled by calling dev_update 
 * on every timer interrupt. In dev_update check if it is 
 * time to create a tasks new job. If so, make the task runnable.
 * There is a wait queue for every device which contains the tcbs of
 * all tasks waiting on the device event to occur.
 */

struct dev
{
	tcb_t* sleep_queue;
	unsigned long   next_match;
};
typedef struct dev dev_t;

/* devices will be periodically signaled at the following frequencies */
const unsigned long dev_freq[NUM_DEVICES] = {100, 200 , 500, 50};
static dev_t devices[NUM_DEVICES];

/**
 * @brief Initialize the sleep queues and match values for all devices.
 */
void dev_init(void)
{
   /* the following line is to get rid of the warning and should not be needed */
	// puts("dev_init\n");	
   	int i;
	for(i=0;i<NUM_DEVICES;i++){
		devices[i].sleep_queue=(tcb_t *)0;
		devices[i].next_match=global_time+dev_freq[i];
	}
}


/**
 * @brief Puts a task to sleep on the sleep queue until the next
 * event is signalled for the device.
 *
 * @param dev  Device number.
 */
void dev_wait(unsigned int dev __attribute__((unused)))
{	
	tcb_t * cur_tcb = get_cur_tcb();
	
	// insert into the sleep_queue
	cur_tcb->sleep_queue=devices[dev].sleep_queue;
	devices[dev].sleep_queue=cur_tcb;

	dispatch_sleep();
}


/**
 * @brief Signals the occurrence of an event on all applicable devices. 
 * This function should be called on timer interrupts to determine that 
 * the interrupt corresponds to the event frequency of a device. If the 
 * interrupt corresponded to the interrupt frequency of a device, this 
 * function should ensure that the task is made ready to run 
 */
void dev_update(unsigned long millis __attribute__((unused)))
{
	// puts("dev_update\n");
	int i;
	tcb_t * sleep_task;
	tcb_t * next_task;
	int has_update=0;

	for (i=0;i<NUM_DEVICES;i++){
		
		if (devices[i].sleep_queue != NULL){
			if (devices[i].next_match <= millis){
			//wake_up
				has_update=1;
				sleep_task=devices[i].sleep_queue;
				devices[i].sleep_queue = NULL;
				devices[i].next_match = millis + dev_freq[i];
				while (sleep_task != NULL){
			 		next_task=sleep_task->sleep_queue;
					sleep_task->sleep_queue = NULL;
					runqueue_add(sleep_task,sleep_task->cur_prio);
					sleep_task=next_task;			
				}			
			}
		}
	}
	if (has_update)
		dispatch_save();	
}


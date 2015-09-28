/* @file sched.c
 * 
 * @brief Top level implementation of the scheduler.
 *
 * Author: Hailun Zhu <hailunz@andrew.cmu.edu>
 *	   Xinkai Wang <xinkaiw@andrew.cmu.edu>
 * Date 11/23/2014
 */

#include <types.h>
#include <assert.h>
#include <exports.h>

#include <kernel.h>
#include <config.h>
#include "sched_i.h"

#include <arm/reg.h>
#include <arm/psr.h>
#include <arm/exception.h>
#include <arm/physmem.h>

#define NULL 0

tcb_t system_tcb[OS_MAX_TASKS]; /*allocate memory for system TCBs */

void sched_init(task_t* main_task  __attribute__((unused)))
{
	runqueue_init();
	int i=0;
	for (;i< OS_MAX_TASKS;i++){
		system_tcb[i].native_prio=0;
		system_tcb[i].cur_prio=0;
		system_tcb[i].context.r4=0;
		system_tcb[i].context.r5=0;
		system_tcb[i].context.r6=0;
		system_tcb[i].context.r7=0;
		system_tcb[i].context.r8=0;
		system_tcb[i].context.r9=0;
		system_tcb[i].context.r10=0;
		system_tcb[i].context.r11=0;
		system_tcb[i].context.sp=(void *)system_tcb[i].kstack_high;
		system_tcb[i].context.lr=NULL;
		system_tcb[i].holds_lock=0;
		system_tcb[i].sleep_queue=NULL;
	}
}

/**
 * @brief This is the idle task that the system runs when no other task is runnable
 */
 
static void __attribute__((unused)) idle(void)
{
	 enable_interrupts();
	 while(1);
}

/**
 * @brief Allocate user-stacks and initializes the kernel contexts of the
 * given threads.
 *
 * This function assumes that:
 * - num_tasks < number of tasks allowed on the system.
 * - the tasks have already been deemed schedulable and have been appropriately
 *   scheduled.  In particular, this means that the task list is sorted in order
 *   of priority -- higher priority tasks come first.
 *
 * @param tasks  A list of scheduled task descriptors.
 * @param size   The number of tasks is the list.
 */


void allocate_tasks(task_t** tasks  __attribute__((unused)), size_t num_tasks  __attribute__((unused)))
{
	unsigned int i=1;
	task_t * task=*tasks;
	for (;i<=num_tasks;i++){
		
		system_tcb[i].native_prio=i;
		system_tcb[i].cur_prio=i;

		system_tcb[i].context.r4= (uint32_t)task->lambda;
		system_tcb[i].context.r5= (uint32_t)task->data;
		system_tcb[i].context.r6= (uint32_t)task->stack_pos;
		system_tcb[i].context.r7= 0;
		system_tcb[i].context.r8= 0;
		system_tcb[i].context.r9= 0;
		system_tcb[i].context.r10= 0;
		system_tcb[i].context.r11= 0;
		system_tcb[i].context.lr=(void *)&launch_task;
		task++;
		runqueue_add(&system_tcb[i],i);
	}
	// set up the tcb for idle task
	system_tcb[IDLE_PRIO].native_prio=IDLE_PRIO;
	system_tcb[IDLE_PRIO].cur_prio=IDLE_PRIO;
	system_tcb[IDLE_PRIO].context.r4= (uint32_t)idle;
	system_tcb[IDLE_PRIO].context.r5= 0;
	system_tcb[IDLE_PRIO].context.r6= 0;
	system_tcb[IDLE_PRIO].context.r7= 0;
	system_tcb[IDLE_PRIO].context.r8= 0;
	system_tcb[IDLE_PRIO].context.r9= 0;
	system_tcb[IDLE_PRIO].context.r10= 0;
	system_tcb[IDLE_PRIO].context.r11= 0;
	system_tcb[IDLE_PRIO].context.lr=(void *)&launch_task;
	runqueue_add(&system_tcb[IDLE_PRIO],IDLE_PRIO);
	
}


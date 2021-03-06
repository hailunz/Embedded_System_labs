/** @file time.c
 *
 * @brief Kernel timer based syscall implementations
 * Author: Hailun Zhu <hailunz@andrew.cmu.edu>
 *	   Xinkai Wang <xinkaiw@andrew.cmu.edu>
 * Date 11/23/2014
 */

#include <types.h>
#include <config.h>
#include <bits/errno.h>
#include <arm/timer.h>
#include <syscall.h>
#include <exports.h>
extern volatile unsigned long global_time;

unsigned long time_syscall(void)
{
	return global_time;
}



/** @brief Waits in a tight loop for atleast the given number of milliseconds.
 *
 * @param millis  The number of milliseconds to sleep.
 *
 * 
 */
void sleep_syscall(unsigned long millis  __attribute__((unused)))
{
	unsigned long wakeup_time = global_time + millis;
	while (1) {
		if (global_time >= wakeup_time)	
			return;
	}
	return;
}

/** @file ub_test.c
 * 
 * @brief The UB Test for basic schedulability
 *
 * @author Kartik Subramanian <ksubrama@andrew.cmu.edu>
 * @date 2008-11-20
 */

//#define DEBUG 0

#include <sched.h>
#ifdef DEBUG
#include <exports.h>
#endif

 
/**
 * @brief Perform UB Test and reorder the task list.
 *
 * The task list at the end of this method will be sorted in order is priority
 * -- from highest priority (lowest priority number) to lowest priority
 * (highest priority number).
 *
 * @param tasks  An array of task pointers containing the task set to schedule.
 * @param num_tasks  The number of tasks in the array.
 *
 * @return 0  The test failed.
 * @return 1  Test succeeded.  The tasks are now in order.
 */
/* sort the tasks by their priorities */
/*
void sort_tasks(task_t *tasks,size_t num_tasks){
	task_t tmp;
	size_t i,j;
	for (j=0;j<num_tasks-1;j++){
		for (i=0;i<num_tasks-1-j;i++){
			if (tasks[i].T > tasks[i+1].T){
				tmp=tasks[i];
				tasks[i]=tasks[i+1];
				tasks[i+1]=tmp;		
			}	
		}
	}
}*/
/*
double UB_test (int k){
	return ;
}
*/
int assign_schedule(task_t** tasks  __attribute__((unused)), size_t num_tasks  __attribute__((unused)))
{
	
	/*task_t * task = * tasks;
	size_t i;
	double sum_i = 0;
	double sum_k = 0;
	double U_value = 0;

	sort_tasks(task,num_tasks);

	for (i=1;i<num_tasks;i++){
		sum_k = (double)(task->C + task->B)/task->T + sum_i;
		U_value = UB_test(i-1);
		if (sum_k > U_value){
		 	return 0;
		}		
		sum_i += (double) task->C/task->T;			
		task++;
	}
	*/
	return 1;	
}
	



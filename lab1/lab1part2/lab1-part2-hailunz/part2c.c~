/*
 * 18342 lab1-part2
 * Hailun Zhu
 * ID: hailunz
 */

#include <stdlib.h>
#include <stdio.h>

/**
 * Function: oddball
 * Description: Baseline implementation for finding the number that
 *   occurs only once in the array.
 * Arguments:
 *   arr - pointer to start of integer array
 *   len - number of elements in array
 * Return:
 *   The number that occurs only once
 */
#ifdef DEFAULT
int oddball(int *arr, int len) {
	int i, j;
	int foundInner;
	int result = 0;

	for (i = 0; i < len; i++) {
		foundInner = 0;
		for (j = 0; j < len; j++) {
			if (i == j) {
				continue;
			}
			if (arr[i] == arr[j]) {
				foundInner = 1;
			}
		}
		if (foundInner != 1) {
			result = arr[i];
		}
	}

	return result;
}
#endif

/*
 * best version: 
 * a^a=0, a^0=a, so use ^ to find the odd one.
 * loop unrolling 
 */
#ifdef OPTIMIZE1
int oddball(int *arr, int len) {
	/* Put your code here */
	int i,j;
	j=0;
	for (i=0;i<len-4;i+=4){
		j=j^arr[i]^arr[i+1]^arr[i+2]^arr[i+3];	
	}
	// finish the remained items.
	for (;i<len;i++){
		j=j^arr[i];
	}
	return j;
}
#endif
/*
 * a^a=0, a^0=a, so use ^ to find the odd one.
 */
#ifdef OPTIMIZE2
int oddball(int *arr, int len) {
	/* Put your code here */
	int i,j;
	j=0;
	for (i=0;i<len;i++){
		j=j^arr[i];	
	}
	return j;
}
#endif

/**
 * Function: randGenerator
 * Description: Generate a random array that is in compliance with
 *   lab specification
 * Arguments:
 *   arr - pointer to start of integer array
 *   len - number of elements in array
 * Return:
 *   Unused, but feel free to utilize it.
 */

int randGenerator(int *arr, int len) {
	int i, j, r, rcount;
	for (i = 0; i < len; i++) {
		do {
			rcount = 0;
			r = rand()%(len/2 + 1) + 1;
			for (j = 0; j < i && rcount < 2; j++) {
				if (arr[j] == r) {
					rcount++;
				}
			}
		} while(rcount >= 2);
		arr[i] = r;
		printf("%d ", r);
	}
	printf("\nDone generating\n");
	return 0;
}





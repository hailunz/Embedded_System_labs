/*
 * rot13.c: ROT13 cipher test application
 *
 * Authors: Hailun Zhu<hailunz@andrew.cmu.edu>
 * Date:    02 OCT, 2014
 */

#include <stdlib.h>
#include <unistd.h>
#define MAXSIZE 256

int main(int argc, char *argv[]) {
	/* Needs more code. */
	char buf[MAXSIZE];
	int size = 0;
	int i = 0;

	// print the parameters
	write(1,"parameters: ",20);
	for (i=0;i<argc;i++){
	    	write(1,argv[i],MAXSIZE);
	    	write(1,", ",5);
	}
	    	write(1,"\n",5);

	while(1){
		// if read return error, exit with 1
		if ((size=read(STDIN_FILENO,buf,MAXSIZE))<0)
			exit(1);
		// if input is 0 byte, only \n, exit with 0
		if (size==0)
			exit(0);
		
		// rot13
 		for(i=0;i<size;i++){
			if ((buf[i]<78)&&(buf[i]>64)){
				buf[i]=buf[i]+13;
			}
			else if ((buf[i]<110)&&(buf[i]>96)){
				buf[i]=buf[i]+13;
			}	
			else if ((buf[i]>77)&&(buf[i]<91)){
				buf[i]=buf[i]-13;
			}
			else if ((buf[i]>109)&&(buf[i]<123)){
				buf[i]=buf[i]-13;
			}

	     	}
		// if write return error, exit with 1
		if(write(STDOUT_FILENO,buf,size)<0)
			exit(1);		
	}	
	return 0;
}

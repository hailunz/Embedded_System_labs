/** @file io.c
 *
 * @brief Kernel I/O syscall implementations
 *
 * Author: Hailun Zhu <hailunz@andrew.cmu.edu>
 *	   Xinkai Wang <xinkaiw@andrew.cmu.edu>
 * Date 11/23/2014
 */

#include <types.h>
#include <bits/errno.h>
#include <bits/fileno.h>
#include <arm/physmem.h>
#include <syscall.h>
#include <exports.h>
#include <kernel.h>

#define EOT_CHAR 0x04
#define DEL_CHAR 0x7f

#define SDRAM_START 0xa0000000
#define SDRAM_END 0xa3ffffff //supervisor mode
#define SFROM_START 0x00000000
#define SFROM_END 0x00ffffff

/* Read count bytes (or less) from fd into the buffer buf. */
ssize_t read_syscall(int fd __attribute__((unused)), void *buf __attribute__((unused)), size_t count __attribute__((unused)))
{

 char * buffer=(char *)buf;
	size_t i=0;
	char tmp;
	size_t addr=(size_t) buf;
	// check fd
	if (fd != STDIN_FILENO)
		return -EBADF;	

	// check buf range
	if ((addr <(size_t)SDRAM_START) ||
       ((addr+count)>(size_t)SDRAM_END))
		return -EFAULT;	
	
	// read
	while (i < count) {
		tmp=getc();
		// check EOT
		if (tmp == 4)
			return i;
		
		// check backspace or delete
		else if ((tmp == 8)||(tmp == 127)){
			if (i > 0)
		                buffer[--i]=0;
			puts("\b \b");	
		}
		// check newline or carriage return
		else if ((tmp == 10)||(tmp == 13)){
            		buffer[i]=10;
            		putc(tmp);
	    		puts("\n");
            		return ++i;
		}
		else {
            		buffer[i]=tmp;
            		putc(tmp);
            		i++;
		}
		
	}
	// return size
	puts("\n");
	return i;
	
}

/* Write count bytes to fd from the buffer buf. */
ssize_t write_syscall(int fd  __attribute__((unused)), const void *buf  __attribute__((unused)), size_t count  __attribute__((unused)))
{

  char *buffer= (char *)buf;
	char tmp;
	//printf("write fd:%d,buf:%x,size:%x\n",fd,&buffer,count);
    
	size_t i=0;//size
   	size_t addrStart=(size_t) buf;
   	size_t addrEnd= addrStart+count;
    
	// check fd	
	if (fd != STDOUT_FILENO)
		return -EBADF;
	// check range
	if((addrStart<(size_t)SDRAM_START)||(addrEnd>(size_t)SDRAM_END)){
      	 if (addrEnd>(size_t)SFROM_END){
		return -EFAULT;	
		} 
	}
	while (i < count){
		tmp=buffer[i];
		if (tmp == 0){
           		 return i;
		}
		putc(tmp);
		i++;
	}
	return i;
	
}


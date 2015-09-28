#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/* This is the function to focus on for optimization */
extern void strTable(char *s, char *d, int sl, int dl);

int main()
{
   /* Assume that dst[i] is always >= 23 (decimal) */
   char src[] = "theinitialstring\n";
   char dst[] = "PENGUINS";
   int i, srcLen, dstLen; 
   
   srcLen = ((strlen(src) >> 2) << 2);
   dstLen = ((strlen(dst) >> 2) << 2);

   printf("PRE: src: %s (%d bytes), dst: %s (%d bytes)\n", 
	  src, srcLen, dst, dstLen); 
   
   for (i=0; i<1000; i++)
     strTable(src, dst, srcLen, dstLen); 
   
   printf("POST: src: %s (%d bytes), dst: %s (%d bytes)\n", 
	  src, srcLen, dst, dstLen);

   // check the string with same 'ip', char < 46   
   /* Assume that dst[i] is always >= 23 (decimal) */
   char src1[] = "theinitialstring\n";
   char dst1[] = "!*#8";
   
   srcLen = ((strlen(src1) >> 2) << 2);
   dstLen = ((strlen(dst1) >> 2) << 2);

   printf("PRE: src: %s (%d bytes), dst: %s (%d bytes)\n", 
	  src1, srcLen, dst1, dstLen); 
   
   for (i=0; i<1000; i++)
     strTable(src1, dst1, srcLen, dstLen); 
   
   printf("POST: src1: %s (%d bytes), dst1: %s (%d bytes)\n", 
	  src1, srcLen, dst1, dstLen);
   
   // check char > 23*4 
   char src2[] = "theinitialstring\n";
   char dst2[] = "EFGHabcd";
   
   srcLen = ((strlen(src2) >> 2) << 2);
   dstLen = ((strlen(dst2) >> 2) << 2);

   printf("PRE: src2: %s (%d bytes), dst2: %s (%d bytes)\n", 
	  src2, srcLen, dst2, dstLen); 
   
   for (i=0; i<1000; i++)
     strTable(src2, dst2, srcLen, dstLen); 
   
   printf("POST: src2: %s (%d bytes), dst2: %s (%d bytes)\n", 
	  src2, srcLen, dst2, dstLen);
   
   return 1;
}


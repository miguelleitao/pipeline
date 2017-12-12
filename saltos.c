/*

	saltos.c

*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include <unistd.h>

#define TIME_DIF(t2,t1) ( (long)((t2).tv_sec-(t1).tv_sec) * 1000000L + (long)((t2).tv_usec-(t1).tv_usec) )

#define TAB_SIZE (80000*1024)

unsigned char Tab[TAB_SIZE];

void TestaSaltos()
{
  struct timeval  t0, t1 ;
  struct timezone tz;
  int I1, I2, I3, I4, I5, I6, I7, I8;
  I1 = I2 = I3 = I4 = I5 = I6 = I7 = I8 = 0;
  int i;
  sleep(4);
  gettimeofday(&t0,&tz);
  for( i=0 ; i<TAB_SIZE ; i++ )
  {
    register unsigned char tabi = Tab[i];
    if (tabi & 0x01)    I1 = I1+1;
    if (tabi & 0x02)    I2 = I2+1;
    if (tabi & 0x04)    I3 = I3+1;
    if (tabi & 0x08)    I4 = I4+1;
    if (tabi & 0x10)    I5 = I5+1;
    if (tabi & 0x20)    I6 = I6+1;
    if (tabi & 0x40)    I7 = I7+1;
    if (tabi & 0x80)    I8 = I8+1;
  }
  gettimeofday(&t1,&tz);
  printf("  Time: %ld msegs\n",  TIME_DIF(t1,t0)/1000L);
  long total = I1+I2+I3+I4+I5+I6+I7+I8;
  printf("  Branches taken: %ld (%3.2f%%)\n",  total, (double)total*100./(double)TAB_SIZE/8. );
  //printf("\tI1:%d\n\tI2:%d\n\tI3:%d\n\tI4:%d\n\tI5:%d\n\tI6:%d\n\tI7:%d\n\tI8:%d\n",
  //	 I1, I2, I3, I4, I5, I6, I7, I8);
}

void CreatePattern(int pat_len)
{
  printf("\nPattern length: %d\n",pat_len);
  int i;
  for( i=0 ; i<pat_len ; i++ )
          Tab[i] = (unsigned char)((float)rand()/(float)(RAND_MAX)*256.);

  for( i=pat_len ; i<TAB_SIZE ; i++ )
          Tab[i] = Tab[i%pat_len];
}


int main()
{
  int i;

  printf("\nNo branches taken\n");
  for( i=0 ; i<TAB_SIZE ; i++ )
    Tab[i] = (unsigned char)0x00;
  TestaSaltos();

  printf("\nAll branches taken\n");  
  for( i=0 ; i<TAB_SIZE ; i++ )
    Tab[i] = (unsigned char)0xff;
  TestaSaltos();

  printf("\nRandom\n");
  for( i=0 ; i<TAB_SIZE ; i++ )
    Tab[i] = (unsigned char)((float)rand()/(float)(RAND_MAX)*256.);
  TestaSaltos();

  printf("\nAlternate\n"); 
  for( i=0 ; i<TAB_SIZE ; i+=1 )
          Tab[i] = (unsigned char)0x55;
  TestaSaltos();

  CreatePattern(2);
  TestaSaltos();

  CreatePattern(4);
  TestaSaltos();

  CreatePattern(16);
  TestaSaltos();

  CreatePattern(64);
  TestaSaltos();

  CreatePattern(256);
  TestaSaltos();

  CreatePattern(1024);
  TestaSaltos();

  CreatePattern(TAB_SIZE);
  TestaSaltos();

  return 0;
}

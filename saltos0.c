/*

	saltos.c

	Compilar com: gcc -o saltos saltos.c
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>

#define TIME_DIF(t2,t1) ( ((t2).tv_sec-(t1).tv_sec) * 1000000L + ((t2).tv_usec-(t1).tv_usec) )

#define TAB_SIZE 80000000

unsigned char Tab[TAB_SIZE];

TestaSaltos()
{
  struct timeval  t0, t1 ;
  struct timezone tz;
  int I1, I2, I3, I4, I5, I6, I7, I8;
  I1 = I2 = I3 = I4 = I5 = I6 = I7 = I8 = 0;
  int i;
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
  printf("  Tempo: %ld msegs\n",  TIME_DIF(t1,t0)/1000);
  printf("  %s%ld\n\tI1:%d\n\tI2:%d\n\tI3:%d\n\tI4:%d\n\tI5:%d\n\tI6:%d\n\tI7:%d\n\tI8:%d\n",
	 "Saltos efectuados: ",  I1+I2+I3+I4+I5+I6+I7+I8, I1, I2, I3, I4, I5, I6, I7, I8);
}


main()
{
  int i;

  printf("\n# Aleatorio\n");
  for( i=0 ; i<TAB_SIZE ; i++ )
    Tab[i] = (unsigned char)((float)rand()/(float)(RAND_MAX)*256.);
  TestaSaltos();

  printf("\n# Padrao com periodo 1\n"); 
  for( i=0 ; i<TAB_SIZE ; i+=1 )
  {
          Tab[i] = (unsigned char)0x55;
  }
  TestaSaltos();

  printf("\n# Padrao com periodo 2\n"); 
  // TestaSaltos();

  printf("\n# Padrao com periodo 3\n");
  // TestaSaltos();
 
  printf("\n# Padrao com periodo 4\n"); 
  // TestaSaltos();

  printf("\n# Padrao com periodo 8\n"); 
  // TestaSaltos();
}


/*
	pipe2.c
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

time_t tempo0, tempo1, tempo2, tempo3;


#define RES_I1	resI1 = (resI1*i + i + 5) / (i+1); \
		resI1 = (resI1*j + j + 5) / (j/3+1)

#define RES_I2  resI2 = (resI2*i + i + 5) / (i+1); \
                resI2 = (resI2*j + j + 5) / (j/3+1)


#define MAX_J 2000
#define MAX_I 30000

void *CalcInt1(void *in)
{
  int i, j;
  int resI1 = 1;
  for( j=0 ; j<MAX_J ; j++ )
  for( i=0 ; i<MAX_I ; i++ )
  {
      RES_I1; RES_I1;
      RES_I1; RES_I1;
      RES_I1; RES_I1;
      RES_I1; RES_I1;
      RES_I1; RES_I1;
  }
  printf("resI1 = %d\n", resI1);
}

void *CalcInt2(void *in)
{
  int i, j;
  int resI2 = 1;
  for( j=0 ; j<MAX_J ; j++ )
  for( i=0 ; i<MAX_I ; i++ )
  {
    RES_I2;  RES_I2;
    RES_I2;  RES_I2;
    RES_I2;  RES_I2;
    RES_I2;  RES_I2;
    RES_I2;  RES_I2;
  }
  printf("resI2 = %d\n", resI2);

}

void *CalcAll(void *in)
{
  int i, j;
  int resI1 = 1;
  int resI2 = 1;
  for( j=0 ; j<MAX_J ; j++ )
  for( i=0 ; i<MAX_I ; i++ )
  {
    RES_I2;  RES_I2;
    RES_I2;  RES_I2;
    RES_I2;  RES_I2;
    RES_I2;  RES_I2;
    RES_I2;  RES_I2;

    RES_I1; RES_I1;
    RES_I1; RES_I1;
    RES_I1; RES_I1;
    RES_I1; RES_I1;
    RES_I1; RES_I1;
  }
  printf("resI1= %d, resI2=%d\n", resI1, resI2);

}

void *CalcAll2(void *in)
{
  int i, j;
  int resI1 = 1;
  int resI2 = 1;
  for( j=0 ; j<MAX_J ; j++ )
  for( i=0 ; i<MAX_I ; i++ )
  {
    RES_I1; RES_I2;
    RES_I1; RES_I2;
    RES_I1; RES_I2;
    RES_I1; RES_I2;
    RES_I1; RES_I2;

    RES_I1; RES_I2;
    RES_I1; RES_I2;
    RES_I1; RES_I2;
    RES_I1; RES_I2;
    RES_I1; RES_I2;
  }
  printf("resI1= %d, resI2=%d\n", resI1, resI2);
}

main()
{
  printf("\n# Em separado\n");
  time(&tempo0);
  CalcInt1(NULL);
  time(&tempo1);
  CalcInt2(NULL);
  time(&tempo2);
  printf("CalcInt: %ld segs,  CalcFloat: %ld segs, Tempo_Total: %ld segs\n", tempo1-tempo0, tempo2-tempo1, tempo2-tempo0);

  printf("\n# Em conjunto, grupos de 10\n");
  time(&tempo0);
  CalcAll(NULL);
  time(&tempo3);
  printf("Tempo: %ld segs\n", tempo3-tempo0);

  printf("\n# Em conjunto, grupos de 1\n");
  time(&tempo0);
  CalcAll2(NULL);
  time(&tempo3);
  printf("Tempo: %ld segs\n", tempo3-tempo0);

}

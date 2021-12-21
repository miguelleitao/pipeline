
/*
	pipe.c
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
//#include <pthread.h>

time_t tempo0, tempo1, tempo2, tempo3;

#define RES_F 	resF = (resF*(float)i + (float)i) / (((float)i)+2.); \
		resF = (resF*(float)j + (float)j) / (((float)j)+2.)

#define RES_I 	resI = (resI*(2*i+j) + i*17 + 5*(i%(j+43)) ) / (i+1); \
		resI = (resI*j + (j+i+5)*13) / (j/3+1); \
		resI = (resI*(3*i+j) + i*19 + 5*(i%(j+47)) ) / (i+1); \
                resI = (resI*j + (j+i+3)*11) / (j/5+1); \


#define MAX_J 2000
#define MAX_I 30000

void *CalcInt(void *in)
{
  int i, j;
  int resI = 1;
  for( j=0 ; j<MAX_J ; j++ )
  for( i=0 ; i<MAX_I ; i++ )
  {
      RES_I; RES_I;
      RES_I; RES_I;
      RES_I; RES_I;
      RES_I; RES_I;
      RES_I; RES_I;
  }
  time(&tempo1);
  printf("resI = %d\n", resI);
}

void *CalcFloat(void *in)
{
  int i, j;
  float resF = 1.;
  for( j=0 ; j<MAX_J ; j++ )
  for( i=0 ; i<MAX_I ; i++ )
  {
    RES_F;  RES_F;
    RES_F;  RES_F;
    RES_F;  RES_F;
    RES_F;  RES_F;
    RES_F;  RES_F;
  }
  time(&tempo2);
  printf("resF = %f\n", resF);
}

void *CalcAll(void *in)
{
  int i, j;
  float resF = 1.;
  int resI = 1;
  for( j=0 ; j<MAX_J ; j++ )
  for( i=0 ; i<MAX_I ; i++ )
  {
    RES_F;  RES_F;
    RES_F;  RES_F;
    RES_F;  RES_F;
    RES_F;  RES_F;
    RES_F;  RES_F;

    RES_I; RES_I;
    RES_I; RES_I;
    RES_I; RES_I;
    RES_I; RES_I;
    RES_I; RES_I;
  }
  time(&tempo2);  printf("resI = %d, resF=%f\n", resI, resF);
}

void *CalcAll2(void *in)
{
  int i, j;
  float resF = 1.;
  int resI = 1;
  for( j=0 ; j<MAX_J ; j++ )
  for( i=0 ; i<MAX_I ; i++ )
  {
    RES_I; RES_F;
    RES_I; RES_F;
    RES_I; RES_F;
    RES_I; RES_F;
    RES_I; RES_F;

    RES_I; RES_F;
    RES_I; RES_F;
    RES_I; RES_F;
    RES_I; RES_F;
    RES_I; RES_F;
  }
  time(&tempo2);
  printf("res2 = %d, %f\n", resI, resF);
}

main()
{
  pthread_t pt1, pt2;

  printf("\n# Em separado\n");
  time(&tempo0);
  CalcInt(NULL);
  time(&tempo1);
  CalcFloat(NULL);
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

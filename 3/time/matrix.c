#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <sys/time.h>
#define MILLION 1000000

void *mat(void *t);

int a[3][2]={{1,2},{3,4},{5,6}};
int b[2][3]={{1,2,0},{0,0,3}};
int c[3][3]={0,};
int d[3][3]={0,};
int p=3,q=2,r=2,s=3;

int main(void)
{
	struct timeval tpstart, tpend;
 	long timediff;

	printf("행렬 A\n"); 	//행렬 A의 값 표시
		
	int i, j, k;
	
	for(i=0; i<p; i++)
	{
		for(j=0; j<q; j++)
		{
			printf("%d ", a[i][j]);
		}
		printf("\n");
	}
	
	printf("\n행렬 B\n"); 	//행렬 B의 값 표시
		
	for(i=0; i<r; i++)
	{
		for(j=0; j<s; j++)
		{
			printf("%d ", b[i][j]);
		}
		printf("\n");
	}
	
    
	gettimeofday(&tpstart, NULL); //계산시작 시간 측정	
	
	for(i=0; i<p; i++)
	{
		for(j=0; j<s; j++)
		{	
			for(k=0; k<q; k++)
			{
				c[i][j] += a[i][k] * b[k][j]; //행렬 AxB의 연산 결과를 행렬 C에 저장
			}
		}
	}
	
     gettimeofday(&tpend, NULL);  //계산종료 시간 측정

	printf("\n두 행렬의 곱 AxB는\n");	//계산결과 행렬 C출력
	
	for(i=0; i<p; i++)
	{
		for(j=0; j<s; j++)
		{
			printf("%d ", c[i][j]);
		}
		printf("\n");
	}
	
    timediff = MILLION*(tpend.tv_sec - tpstart.tv_sec) + tpend.tv_usec - tpstart.tv_usec;
	printf("\n(싱글 쓰레드) \nIt took %ld msec \n\n", timediff);
	//수행시간 계산후 표시
	
	// 이번엔 멀티쓰레드 사용하여 행렬계산
	
	pthread_t thread[p];
	int rc;
	void *status;
	
	gettimeofday(&tpstart, NULL); //계산시작 시간 측정

     for(i=0; i<p; i++)
     {
         rc= pthread_create(&thread[i],NULL ,mat,(void *)&i); //쓰레드 생성
		 if (rc){
			 printf("error");
			 exit(-1);
		 }

     }

	 for(i=0; i<p; i++)
	 {
		rc= pthread_join(thread[i], &status);	//쓰레드 끝날때까지 대기
		if (rc){
			printf("error2");
			exit(-1);
		}
	 }

      gettimeofday(&tpend, NULL);  //계산종료 시간 측정

     printf("\n두 행렬의 곱 AxB는\n");	//계산결과 출력

     for(i=0; i<p; i++)
     {
         for(j=0; j<s; j++)
         {
             printf("%d ", d[i][j]);
         }
         printf("\n");
     }

     timediff = MILLION*(tpend.tv_sec - tpstart.tv_sec) + tpend.tv_usec - tpstart.tv_usec;
     printf("\n(멀티 쓰레드) \nIt took %ld msec \n\n", timediff);
	//수행시간 출력
	return 0;
}

//행렬 계산 쓰레드, 한 행씩 값을 계산한다.

void *mat(void *t) 
{
	int i,j,k;
	i = *(int *)t;

	for(j=0; j<s; j++)
	{
		for(k=0; k<q; k++)
		{
			d[i][j] += a[i][k] * b[k][j];
		}
	}
	
	pthread_exit((void*) t);
}


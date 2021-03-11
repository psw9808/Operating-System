#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
 

volatile int global = 100; //전역변수 global 선언
pthread_mutex_t mutex_lock; //뮤텍스 객체 선언

void *BusyWork(void *t)
{
   int i;
   long tid;
   double result=0.0;
   tid = (long)t;
   printf("Thread %ld starting...\n",tid);

   for (i=0; i<1000000; i++)
   {

   pthread_mutex_lock(&mutex_lock);	//다른 쓰레드에서 공유자원 사용하지 못하도록 잠금
		global--;					//전역변수 변경 작업
		global++;
   pthread_mutex_unlock(&mutex_lock); //작업 후 쓰레드 공유자원 잠금해제
   }

 
   printf("Thread %ld done. Result = %d\n",tid, global);
   pthread_exit((void*) t);
}


int main (int argc, char *argv[])
{
	int NUM_THREADS;
	pthread_mutex_init(&mutex_lock, NULL); //뮤텍스 객체 초기화

	printf("전역변수 100에서 1빼고 1더하는 쓰레드를 여러번 실행해보자\n");
	printf("number of threads :");
	scanf("%d",&NUM_THREADS);
   pthread_t thread[NUM_THREADS];
   int rc;
   long t;
   void *status;

   for(t=0; t<NUM_THREADS; t++) {
      rc = pthread_create(&thread[t], NULL, BusyWork, (void *)t); 
      if (rc) {
         printf("ERROR; return code from pthread_create()is %d\n", rc);
         exit(-1);
         }
	 // rc = pthread_join(thread[t], &status);
	 // 여기에 쓰레드 조인넣으면 쓰레드 실행 종료 후 그다음 쓰레드 생성한다.
      }

   for(t=0; t<NUM_THREADS; t++) {
      rc = pthread_join(thread[t], &status); //쓰레드 종료하면 메세지와 함께 결과 출력
      if (rc) {
         printf("ERROR; return code from pthread_join() is %d\n", rc);
         exit(-1);
      }
   }
   printf("Main: program completed. Exiting.\n"); //마지막에 메인 프로그램 종료 출력
   pthread_exit(NULL);
}
	

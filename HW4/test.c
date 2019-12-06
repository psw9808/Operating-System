#include <stdio.h>
#include <stdlib.h>
#define stacksize 102457600
#define heapsize 1024576000
int makestack(int num,int num2);
int makeheap(int num);
void *heap;

int main()
{
	int stacknum = 0;
	int heapnum = 0;
	int i;

	for(i=0;i<10000000;i++){
	
	makestack(stacknum,0);
	stacknum++;

	heap = (void *)malloc(heapsize);
	printf(" heap  %3d   %p\n",heapnum,heap);
	heapnum++;
	}
	return 0;
}

int makestack(int num,int num2){
	int stack[stacksize];
	
	if(num==num2){
	printf("stack  %3d   %p \n",num,stack);
	}
	else{
	num2++;
	makestack(num,num2);
	}
}


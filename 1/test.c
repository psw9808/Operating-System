#pragma warning(disable:4996)
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct node {		//node 정의
	void* datap;			//data 저장할 주소
	struct node* nextp;		//다음 노드 주소를 가리킬 주소
}node;

typedef struct {			//stack 정의
	int* count;				//stack 의 노드 갯수
	struct node* top;		//top의 주소를 가리킬 주소
}stack;

stack* cstack()								//stack 생성
{
	stack *st;
	st = (stack*)malloc(sizeof(stack));		//stack에 메모리 할당
	st->count = 0;							//초기 스택노드 갯수 초기화
	st->top = NULL;							//초기 탑 주소 초기화
	return st;
}

void push(stack* st, void* itemp)			//push 함수
{
	node *newn;								//새로운 노드 newn 생성
	newn = (node*)malloc(sizeof(node));		//newn 에 메모리 할당
	if (newn == NULL)						//메모리 할당이 안될 경우 종료
		return;

	newn->datap = itemp;					//newn의 데이터 주소에 입력받은 정보 저장
	newn->nextp = st->top;					//newn의 다음 주소에 현재 스택의 탑 주소 저장
	st->top = newn;							//스택 탑주소에 newn 주소 저장
	st->count++;							//스택 노드갯수 +1
}

int pop(stack* st)							//pop 함수
{
	if (st->count == 0)						//스택 노드 갯수가 0이면 종료
		return 0;
	else {
		int topdata;						//탑노드 정보를 저장할 변수 선언
		node *oldtop = st->top;				//탑노드 주소를 저장할 노드주소 선언
		topdata = *(int*)oldtop->datap;			//탑노드 정보 int변수에 저장
		st->top = oldtop->nextp;			//탑노드 주소에 다음노드 주소 저장
		free(oldtop);						//이전 탑노드 메모리 할당 해제
		st->count--;						//스택 노드갯수 -1
		return topdata;					//탑 데이터 반환
	}
	
}

void dstack(stack* st)			//stack 삭제 함수
{
	while (st->count != 0) {	//노드 갯수가 0이 될때까지 pop 반복
		pop(st);
	}
	free(st);					//스택 메모리 할당 해제
}

typedef struct {			//queue 정의
	int count;				//큐 노드 갯수
	struct node* front;		//큐의 첫노드 주소
	struct node* rear;		//큐의 끝노드 주소
}queue;

queue* cqueue()							//queue 생성
{
	queue *qu;
	qu = (queue*)malloc(sizeof(queue));	//큐에 메모리 할당
	qu->count = 0;						//큐의 노드갯수, 앞/끝부분 주소 초기화
	qu->front = NULL;
	qu->rear = NULL;
	return qu;
}

void enqueue(queue* qu, void* itemp)			//enqueue 함수
{
	node *newn = (node*)malloc(sizeof(node));	//새 노드 newn에 메모리 할당
	if (newn == NULL)							//메모리 할당 실패시 종료
		return;
	else if (qu->count == 0)							//큐 노드갯수 0일 때
	{
		newn->datap = itemp;					//newn에 입력 데이터 저장
		qu->front = newn;						// qu의 앞과 끝 주소에 newn 주소 저장
		qu->rear = newn;
		newn->nextp = NULL;						//newn의 다음주소는 NULL로 초기화
		qu->count++;
	}
	else
	{											//큐에 노드가 하나이상 있을 때
		node* t = qu->rear;						//이전 노드 포인터 t 선언
		newn->datap = itemp;					
		t->nextp = newn;						//이전 노드의 다음주소에 newn주소 저장
		qu->rear = newn;
		newn->nextp = NULL;
		qu->count++;
	}
}

int dequeue(queue* qu)					//dequeue 함수
{
	if (qu->count == 0)					//큐 노드갯수 0이면 종료
		return 0;
	else if (qu->count == 1) {			//큐 노드갯수 1개일때 
		node* t = qu->front;			//앞 노드 주소를 저장할 포인터 t 선언
		qu->front = NULL;				//큐의 앞과 뒤 노드 초기화
		qu->rear = NULL;
		qu->count--;					
		int item = *(int*)t->datap;	//맨앞 노드 데이터 저장
		free(t);						//맨앞 노드 메모리 할당 해제
		return item;
	}
	else {								//큐 노드갯수 여러개일때
		node* t = qu->front;			
		qu->front = t->nextp;			//큐의 맨앞에 주소를 다음 노드 주소로 바꿈
		qu->count--;					
		int item = *(int*)t->datap;
		free(t);
		return item;
	}
}

void dqueue(queue* qu)			//큐 삭제 함수
{
	while (qu->count != 0)		//큐 노드 갯수가 0이 될 때까지 디큐한다
	{
		dequeue(qu);
	}
	free(qu);					//큐 메모리 할당 해제
}

int main(void) {

	char s1[100];					//입력받을 문자열 선언
	int s2[100];					//숫자 배열 선언
	int countnum = 0;				//입력 숫자 카운터 선언
	int num,i;

	fgets(s1,100,stdin);			//문자열 입력 받기

	char *ptr = strtok(s1, " ");	//입력받은 문자열 strtok로 나누기

	while (ptr != NULL)
	{
		num = atoi(ptr);			//문자열 -> 숫자 변환 함수 사용
		s2[countnum++] = num;		//변환값 숫자 배열에 저장
		ptr = strtok(NULL, " ");
	}

	printf(" stack: ");
	stack* stack = cstack();			//스택 생성
	for (i = 0; i < countnum; i++) {
		push(stack, &s2[i]);				//스택에 숫자 배열 push
	}
	for (i = 0; i < countnum; i++) {
		printf("%d ", pop(stack));		//pop 으로 출력
	}
	dstack(stack);						//스택 삭제

	printf("\n queue: ");
	queue* queue = cqueue();			//큐 생성
	for (i = 0; i < countnum; i++) {
		enqueue(queue, &s2[i]);			//큐에 숫자 배열 enqueue
	}
	for (i = 0; i < countnum; i++) {
		printf("%d ", dequeue(queue));	//dequeue로 출력
	}
	dqueue(queue);						//큐 삭제

	printf("\n");
	return 0;
}

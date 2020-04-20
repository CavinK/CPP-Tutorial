#include <stdio.h>
#include <stdlib.h>
#include "stack_list.h"

void main(void)
{
	init();
	
	// 스택에 원소 넣기
	push('A');
	push('B');
	push('C');
	push('D');
	printStack();	
	
	// 스택 원소 꺼내기
	printf("스택에서 %c를 꺼냈습니다.\n", pop());
	printf("스택에서 %c를 꺼냈습니다.\n", pop());
	printStack();	

	// 스택에 원소 넣기
	push('O');
	push('P');
	printStack();	

	// 스택 원소 꺼내기
	printf("스택에서 %c를 꺼냈습니다.\n", pop());
	printf("스택에서 %c를 꺼냈습니다.\n", pop());
	printf("스택에서 %c를 꺼냈습니다.\n", pop());
	printf("스택에서 %c를 꺼냈습니다.\n", pop());
	printf("스택에서 %c를 꺼냈습니다.\n", pop());
}
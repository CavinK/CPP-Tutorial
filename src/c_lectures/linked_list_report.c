#include <stdio.h>
#include <stdlib.h>
#include "linked_list.h"

void main()
{
	// 노드 타입 포인터
	nodeType *head, *temp;
	// 연결리스트 생성
	temp = (nodeType*)malloc(sizeof(nodeType)); // 첫번째 노드 생성
	temp->item = 'C';
	temp->next = NULL;
	head = temp; // 생성된 노드를 첫번째 노드로 지정

	temp = (nodeType*)malloc(sizeof(nodeType)); // 두번째 노드 생성
	temp->item = 'D';
	temp->next = head;
	head = temp;

	temp = (nodeType*)malloc(sizeof(nodeType));
	temp->item = 'E';
	temp->next = head;
	head = temp;
	
	printList(head);
}

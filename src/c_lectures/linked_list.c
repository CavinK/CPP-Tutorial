#include <stdio.h>
#include <stdlib.h>
#include "linked_list.h"

void main()
{
	
	nodeType *head, *temp;
    
	temp = (nodeType*)malloc(sizeof(nodeType));
	temp->item = 'A';
	temp->next = NULL;
	head = temp;    //생성된 노드를 첫번재 노드로 지정
	
	temp = (nodeType*)malloc(sizeof(nodeType));
	temp->item = 'B';
	temp->next = NULL;
	insertNext(head, temp);   // 생성된 노드를 삽입
	
	temp = (nodeType*)malloc(sizeof(nodeType));
	temp->item = 'C';
	temp->next = NULL;
	insertNext(head, temp);   // 생성된 노드를 삽입
	
	printList(head);
	
	removeNext(head);
	printList(head);
}


#define MaxStackSize 10       //스택의 최대 크기

typedef struct Node
{
    char item;         // 노드 데이터
	struct Node* next; //링크  
} nodeType;    

void initList(nodeType *headPtr) { 
	headPtr = NULL; 
}

int isEmpty(nodeType *headPtr) { 
	if (headPtr == NULL) 
		return 1;
	else return 0; 
}

int getCurrentSize(nodeType *headPtr) {
	nodeType *p;
	int count = 0;
	
	for(p=headPtr; p!=NULL; p=p->next)
		count = count + 1;
	
	return count;   
}

char contains(nodeType *headPtr, int pos) { 
	nodeType *p = headPtr;
	int i;
	
	for(i=0; i<pos; p=p->next)
		if (p == NULL) return 0;
	
	return p->item;   
}


void insertNext(nodeType *prevNode, nodeType *newNode)
{
	if (newNode != NULL) {
		newNode->next = prevNode->next;
		prevNode->next = newNode;
	}
}

nodeType* removeNext(nodeType *prevNode)
{
	nodeType *removed = prevNode->next;
	
	if (removed != NULL) 
		prevNode->next = removed->next;
	
	return removed;
}

void printList(nodeType *headPtr)
{
	nodeType *p = headPtr;
	
	printf("리스트의 내용을 출력합니다.\n");
	for (p=headPtr; p != NULL; p=p->next)
		printf("[%c] ", p->item);
	
	printf("\n");
}




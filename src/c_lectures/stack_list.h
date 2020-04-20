#define MaxStackSize 100    //스택의 최대 크기

typedef struct node
{
    char data;
    struct node* next;
} nodeType;     // 노드타입 정의
          
//Top을 가리키는 포인터 선언
nodeType* Stack_top; 

void init() { 
	Stack_top = NULL; 
}

int isEmpty() { 
	if (Stack_top == NULL) 
		return 1;
	else return 0; 
}

int getSize() {
	nodeType *p;
	int count = 0;
	
	for(p=Stack_top; p!=NULL; p=p->next)
		count = count + 1;
	
	return count;   
}

int isFull(){
	return (getSize() == MaxStackSize);
}

void push(char item)
{    
	// 삽입할 노드의 생성
    nodeType* p = (nodeType*)malloc(sizeof(nodeType));
    p->data = item;
     
	// Top의 위치에 노드 삽입
    p->next = Stack_top;
    Stack_top = p;
}

char pop()
{    
	nodeType* p;
	char item;
	
	if(isEmpty()){
		printf("스택이 비어있습니다.\n");
		exit(1);
	} else {
		p = Stack_top;
		Stack_top = Stack_top->next;
		item = p->data;
		free(p);
		return(item);
	}
}

void printStack()
{
	nodeType* p;
	printf("스택의 크기는 %d입니다.\n",getSize());
	for(p=Stack_top; p!=NULL; p=p->next)
		printf("%c\n", p->data);
}





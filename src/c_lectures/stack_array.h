#define MaxStackSize 10       //스택의 최대 크기

typedef struct {
     int Top;           	  //스택의 탑을 표시하는 변수
     int data[MaxStackSize];  //스택의 원소를 저장하는 배열
} stackType;

void init(stackType* Sptr)
{      
  // 탑 인덱스를 -1으로 빈스택을 표시
  Sptr->Top = -1;        
}

int isEmpty(stackType* Sptr)
{     
  // Top < 0 일 경우 비어있다고 판단
  return (Sptr->Top < 0);
}

int  isFull(stackType* Sptr)
{     
   // Top >= MaxStackSize-1 일 경우 꽉 차 있다고 판단
   return (Sptr->Top >= MaxStackSize-1);
}

int getSize(stackType* Sptr)
{
	return (Sptr->Top+1);
}

void push(stackType* Sptr, int Item)
{     
	if (isFull(Sptr)) 
		printf("더이상 넣을 수 없습니다.!!!\n");
    else {
		//data[Top+1]에 데이터 삽입, Top을 1증가
        Sptr->data[Sptr->Top+1] = Item;
        Sptr->Top = Sptr->Top + 1;
	}
}

int pop(stackType* Sptr)
{   
	int temp;
    if (isEmpty(Sptr)){
		printf("스택이 비어있습니다.\n");
        return -1;
     } else {
        //data[Top]의 값을 반환, Top을 1감소
        temp = Sptr->data[Sptr->Top];
        Sptr->Top = Sptr->Top - 1;
        return temp;
    }
}

int peek(stackType* Sptr)
{   
	int temp;
    if (isEmpty(Sptr)){
		printf("스택이 비어있습니다.\n");
        return -1;
     } else {
        //data[Top]의 값을 반환, Top을 1감소
        temp = Sptr->data[Sptr->Top];
        return temp;
    }
}

void printStack(stackType* Sptr)
{
	if (isEmpty(Sptr))
		printf("스택이 비어있습니다.\n");
	else {
		printf("스택의 총 원소 수는 %d입니다.\n", getSize(Sptr));
		
		for (int i = 0; i <= Sptr->Top; i++)
			printf("스택의 %d번째 원소는 %d입니다.\n", i + 1, Sptr->data[i]);
	}
}

void stackPrint(stackType* pArray)
{
	if (pArray->Top < 0)
		printf("Stack is empty.\n");
	else {
		printf("The number of total elements is %d.\n", pArray->Top + 1);
		
		for (int i = 0; i <= pArray->Top; i++)
			printf("The element of index %d is %d.\n", i, pArray->data[i]);
	}
}



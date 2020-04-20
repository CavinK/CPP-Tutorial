#define maxItems	100   // 최대 100개를 저장

// 리스트 구조 정의
int itemCount;          // 리스트의 크기를 저장
int items[maxItems];    // 리스트아이템 타입은 정수형

void initList() { 
	itemCount = 0; 
}

int isEmpty() { 
	if (itemCount == 0) 
		return 1;
	else return 0; 
}

int isFull() { 
	if (itemCount == maxItems)
		return 1;
	else return 0;
}

int getCurrentSize() {
	return itemCount;   
}

int contains(int pos) { 
	return items[pos];  
}

void insert(int pos, int item)
{
	int i;
	if (isFull() == 0 && pos >= 0 && pos <= itemCount) {
		for (i = itemCount; i>pos; i--) // 마지막위치부터 지정한위치까지 
			items[i] = items[i-1];      // 한칸씩 값을 뒤로 이동
		
		items[pos] = item;              // 지정한 위치에 item 값을 넣음 
		itemCount = itemCount + 1 ;     // 리스트 크기를 1증가시킴
	}
	else 
		printf("리스트가 포화상태이거나 삽입 위치가 잘못되었습니다.\n");
}

void delete(int pos)
{
	int i;
	if (isEmpty() == 0 && 0 <= pos && pos<itemCount) {
		for (i = pos+1; i<itemCount; i++)  // 지정한 위치+1부터 마지막까지 
		items[i-1] = items[i];      	   //한칸씩 값을 앞으로 이동
	
		itemCount = itemCount - 1 ;        // 리스트 크기를 1감소시킴
	}
	else 
		printf("리스트가 공백상태이거나 삭제 위치가 잘못되었습니다.\n");
}


void printList()
{
	int i;
	printf("리스트의 내용을 출력합니다.\n");
	for (i = 0; i<itemCount; i++)
		printf("[%d]", items[i]);	
	
	printf("\n");
}









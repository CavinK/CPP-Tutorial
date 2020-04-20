#include <stdio.h>
#include <malloc.h>

typedef struct _node
{
      char Data;
      struct _node *Next;
} nodeType;

void main()
{
      // 노드 타입 포인터
      nodeType *head, *temp;
      // 연결리스트 생성
      temp = (nodeType*)malloc(sizeof(nodeType)); // 첫번째 노드 생성
      temp->Data = 'C';
      temp->Next = NULL;
      head = temp; // 생성된 노드를 첫번째 노드로 지정
   
      temp = (nodeType*)malloc(sizeof(nodeType)); // 두번째 노드 생성
      temp->Data = 'D';
      temp->Next = head;
      head = temp;

      temp = (nodeType*)malloc(sizeof(nodeType));
      temp->Data = 'E';
      temp->Next = head;
      head = temp;

}
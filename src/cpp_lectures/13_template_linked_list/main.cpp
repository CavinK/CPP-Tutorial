#include <iostream>
#include "LinkedList.h"

using namespace std;

int main()
{
	CLinkedList<int> listInt;
	CLinkedList<float> listFloat;
	
	for (int i = 0; i < 100; ++i)
	{
		listInt.push_back(i + 1);
	}
	
	cout << listInt.size() << endl;
	
	CLinkedList<int>::iterator iter; // 리더 클래스 <- iterator는 CLinkedList 안에 정의된 클래스라서 :: 사용!
	// CListIterator<int> iter1; // 이렇게 일반 클래스 선언하듯이 별도 선언 가능!(위와 같은 코드)
	for (iter = listInt.begin(); iter != listInt.end(); ++iter)
	{
		cout << *iter << endl;
	}
	
	cout << "==== reverse ====" << endl;
	CLinkedList<int>::reverse_iterator riter;
	for (riter = listInt.rbegin(); riter != listInt.rend(); ++riter)
	{
		cout << *riter << endl;
	}
	
	return 0;
}
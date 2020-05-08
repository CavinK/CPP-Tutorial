#include <iostream>
#include "Queue.h"

using namespace std;

int main()
{
	CQueue<int> queue;
	
	for (int i = 0; i < 100; ++i)
	{
		queue.push(i + 1);
	}
	
	while (!queue.empty())
	{
		cout << queue.pop() << endl;
	}
	
	CCircleQueue<int, 10> queue1; // SIZE를 지정하지 않으면 100, 이렇게 지정하면 지정한 값으로 배열 크기가 정해짐!
	CCircleQueue<int> queue2;
	CCircleQueue<int, 300> queue3;
	
	cout << "10개 push" << endl;
	for (int i = 0; i < 10; ++i)
	{
		queue1.push(i + 1);
	}
	
	cout << "3개 pop" << endl;
	for (int i = 0; i < 3; ++i)
	{
		cout << queue1.pop() << endl;
	}
	
	cout << "4개 push" << endl;
	for (int i = 0; i < 4; ++i)
	{
		queue1.push(i + 1); // 4개 push 해도 빈 자리가 없어서 3개만 들어감!
	}
	
	cout << "전부 pop" << endl;
	while (!queue1.empty())
	{
		cout << queue1.pop() << endl;
	}
	
	return 0;
}
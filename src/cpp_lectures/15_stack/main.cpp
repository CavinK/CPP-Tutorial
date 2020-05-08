#include <iostream>
// #include "Vector.h"
#include "Stack.h"

using namespace std;

// 리스트: 중간 삽입, 삭제가 많을 때는 이걸 쓰는 게 유리
// 벡터: 단순히 데이터 저장용으로 쓸 때 유리

int main()
{
	// CVector<int> vecInt;
	
	// // vecInt.reserve(100); // resize 안 해도 됨 => 성능이 훨씬 좋아짐!
	
	// for (int i = 0; i < 100; ++i)
	// {
	// 	vecInt.push_back(i + 1);
	// }
	
	// for (int i = 0; i < vecInt.size(); ++i)
	// {
	// 	cout << vecInt[i] << endl; // 인덱스 조회를 operator를 이용해서 정의!
	// }
	
	CStack<int> stackInt;
	
	for (int i = 0; i < 100; ++i)
	{
		stackInt.push(i + 1);
	}
	
	while(!stackInt.empty())
	{
		cout << stackInt.pop() << endl; // First In Last Out!
	}
	
	return 0;
}
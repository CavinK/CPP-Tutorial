#include <iostream>

using namespace std;

int main()
{
	/*
	레퍼런스: 다른 대상을 참조하게 만들어주는 기능이다.
	참조를 하게 되면 그 대상에 접근하여 값을 변경할 수 있다.
	단, 레퍼런스는 처음 레퍼런스 변수 생성 시 참조하는 대상을 지정해 주어야 한다.
	
	변수타입 &레퍼런스명 = 참조할변수명; 으로 한다.
	*/
	int iNumber = 100;
	int iNumber1 = 9999;
	
	// iRefNum 레퍼런스 변수는 iNumber를 참조한다.
	int& iRefNum = iNumber; // 주소를 주는 개념이 아니라 참조만 하는 거!
	
	iRefNum = 1234; // 이런 식으로 참조하는 대상의 값을 바꿀 수 있음!
	
	iRefNum = iNumber1; // 이렇게 하면 iNumber 값 자체가 바뀜!
	
	cout << iNumber << endl;
	cout << sizeof(int&) << endl; // 4바이트
	cout << sizeof(iRefNum) << endl;
	
	return 0;
}
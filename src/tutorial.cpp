#include <iostream>

using namespace std;

/*
코드 작성 => 바이너리 코드라는 실행 파일이 만들어짐 => 실행 파일을 이용해서 프로그램 실행 => 코드가 메모리에 올라감 => 메모리 주소!

함수 포인터: 함수의 메모리 주소를 저장하기 위한 포인터 변수를 선언할 수 있다.
전역 함수의 경우, 함수명이 곧 함수의 메모리 주소이다. <- cf. 배열명: 시작점의 메모리 주소
함수 포인터 선언 방법: 반환타입 (*포인터변수명)(인자타입); 의 형태로 구성이 된다.
*/

int Sum(int a, int b)
{
	return a + b;
}

int OutSub(int a, int b)
{
	cout << a - b << endl;
	return a - b;
}

// 멤버 함수에 대한 포인터의 경우
void Output()
{
	cout << "Output Function" << endl;
}

class CHanzo
{
public:
	CHanzo()
	{
		m_iTest = 10;
	}
	
	~CHanzo()
	{
	}
	
public:
	int m_iTest;
	
public:
	void Output()
	{
		cout << "Hanzo" << endl;
	}
};

int main()
{
	int (*pFunc)(int, int) = Sum; // 포인터 변수 선언! <- Sum() 함수의 반환 타입이 int 
	// 함수명(Sum)이 곧 포인터 주소 <- 위에 처럼 포인터 변수(pFunc)에 함수명을 담아두면, 포인터 변수를 함수처럼 사용 가능!
	
	cout << pFunc(10, 20) << endl;
	
	pFunc = OutSub; // 포인터는 언제든지 가리키는 변수를 바꿀 수 있음 <- 함수도 메모리 주소!
	OutSub(10, 20);
	
	// pFunc = Output; // 에러! <- 리턴 타입이 다르고, 받는 인자 수도 다르기 때문!
	void (*pFunc1)() = Output;
	pFunc1();
	
	return 0;
}
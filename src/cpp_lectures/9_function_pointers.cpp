#include <iostream>
#include <functional>

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

float TestFunc(float a)
{
	cout << a << endl;
	return a;
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
		cout << "Test : " << m_iTest << endl; // this->m_iTest 가 생략되어 있는 거!
	}
};

typedef struct _tagPoint
{
	int x;
	int y;
	
	_tagPoint() :
		x(0),
		y(0)
	{	
	}
	
	_tagPoint(int _x, int _y) :
		x(_x),
		y(_y)
	{	
	}
	
	_tagPoint(const _tagPoint& pt)
	{
		// 얕은 복사를 한다.
		// 이렇게 해줄 경우, this는 자기 자신의 포인터이고,
		// *을 붙여서 자기 자신을 역참조하여 모든 데이터를 복사하게 한다.
		*this = pt; // shallow copy
	}
	
	// operator <- 구조체, 클래스에 사용 가능!
	_tagPoint operator +(const _tagPoint& pt) // +의 연산자 재정의!
	{
		_tagPoint result;
		result.x = x + pt.x;
		result.y = y + pt.y;
		return result;
	}
	
	_tagPoint operator +(int a) // overloading
	{
		_tagPoint pt;
		pt.x = x + a;
		pt.y = y + a;
		return pt;
	}
	
	void operator +=(int a)
	{
		x += a;
		y += a;
	}
	
	void operator ++()
	{
		x++;
		y++;
	}
	
	void operator --()
	{
		x--;
		y--;
	}
	
	void operator << (const _tagPoint& pt)
	{
		x = pt.x;
		y = pt.y;
	}
	
	void operator >> (_tagPoint& pt)
	{
		pt.x = x;
		pt.y = y;
	}
}POINT, *PPOINT;

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
	
	CHanzo hanzo1, hanzo2;
	
	hanzo1.m_iTest = 100;
	hanzo2.m_iTest = 200;
	
	// this 포인터: 클래스 안에서 this를 사용할 경우, 해당 객체의 메모리 주소가 된다.
	// 즉, 자기 자신의 포인터이다.
	// 멤버 함수를 호출할 때, this를 호출자로 세팅한다.
	hanzo1.Output();
	hanzo2.Output(); // 값은 다르지만 Output() 함수의 메모리 주소는 하나! <- this 포인터!
	
	// 멤버 함수 포인터 선언 시 포인터 변수 이름 앞에 클래스명:: 을 붙여준다. <- 범위 지정 연산자
	void (CHanzo::*pFunc2)() = &CHanzo::Output; // 범위 지정 연산자를 사용할 때는 클래스명이 꼭 메모리 주소가 되는 건 아님 => & 추가!
	
	// pFunc2(); // 에러!
	// (*pFunc2)(); // 에러!
	// hanzo1.(*pFunc2)(); // 에러!
	(hanzo1.*pFunc2)(); // 멤버 함수 포인터 호출이 까다로움! => functional 사용!
	
	/*
	function 기능은 C++11 부터 지원을 해주는 기능이다.
	이 기능은 함수 포인터를 전역, 멤버 가리지 않고 쉽게 주소를 저장해서 호출해줄 수 있도록 만들어주는 기능이다.
	
	선언 방법: function<리턴타입(인자타입)> 변수명; 의 형태로 선언한다.
	*/
	function<void()> func; // functional 객체 만듬 <- 전역 함수, 일반 함수 다 넣을 수 있음!
	function<void()> func1;
	
	// bind()를 이용해서 함수를 묶어준다.
	func = bind(Output); // 전역 함수 <- bind(함수포인터, 인자)
	func1 = bind(&CHanzo::Output, &hanzo1); // 멤버 함수 <- bind(클래스주소::함수포인터, 객체주소, 인자)
	// func1 = bind(&CHanzo::Output, &hanzo2); // 객체 주소 바꿔주면 값들도 저절로 바뀜!
	
	cout << "================== Functional =======================" << endl;
	func();
	func1();
	
	function<int(int, int)> func3;
	function<float(float)> func4;
	
	// 함수에 인자가 있을 경우, placeholders 를 이용해서 인자의 순서를 정의할 수 있다.
	// 아래처럼 _2, _1로 넣어주면 인자가 서로 바뀌게 된다.
	func3 = bind(OutSub, placeholders::_1, placeholders::_2); // bind()에 인자값을 넣을 때는 placeholders 사용!
	// func3 = bind(OutSub, placeholders::_2, placeholders::_1); // placeholders의 숫자를 바꿔주면 인자의 순서도 바뀜!!
	func3(10, 20);
	
	func4 = bind(TestFunc, placeholders::_1);
	func4(3.14f);
	
	cout << "============= Point =================" << endl;
	POINT pt1(10, 20), pt2(30, 40), pt3;
	
	// 본래 구조체는 연산이 불가능 => operator를 쓰면 가능해짐!
	// POINT 구조체는 + 연산자가 operator로 재정의 되어 있다.
	// 그래서 + 연산이 가능하게 되고, pt1의 +연산자 함수를 호출해주는 개념이다.
	// pt2를 인자로 넘겨준다.
	pt3 = pt1 + pt2;
	
	pt3 << pt1; // 위의 operator 연산자 재정의를 통해 대입 기능을 만듬!
	pt2 >> pt3;
	
	pt3 = pt1 + 1000;
	
	pt3 += 2000;
	
	++pt3;
	
	cout << "x : " << pt3.x << "\ty : " << pt3.y << endl;
	
	return 0;
}
#include <iostream>

using namespace std;

/*
템플릿: 컴파일 단계에서 타입을 결정짓는 기능이다.
타입이 다양하게 바뀔 수 있다.

template <typename 원하는이름> 의 형태로 사용 가능하다.
template <class 원하는이름> 의 형태로 사용 가능하다.

ex. template <typename T>
void Output()
{
	cout << typeid(T).name() << endl;
}

위처럼 함수를 만들고 호출 시
Output<int>();
Output<float>();

이렇게 해주면 int, float으로 타입이 정해진다.
상황에 따라 넣어주는 타입으로 타입이 가변적으로 바뀌는 것이다.

가변 타입은 여러 개를 지정해줄 수 있다.
template <typename T, typename T1>
void Output()
{
}

위처럼 여러 개 지정도 가능한 것이다.
*/

template <typename T>
void OutputType()
{
	cout << "==== OutputType ====" << endl;
	cout << typeid(T).name() << endl;
}

template <typename T>
void OutputData(T data)
{
	cout << "==== OutputData ====" << endl;
	cout << typeid(T).name() << endl;
	cout << data << endl;
}

typedef struct _tagStudent
{
	
}STUDENT, *PSTUDENT;

class CCar
{
public:
	CCar()
	{
	}
	
	~CCar()
	{
	}
};

enum TEST
{
	
};

class CTemplate
{
public:
	CTemplate()
	{
	}
	
	~CTemplate()
	{
	}
	
public:
	template <class T, class T1> // 이런 식으로 클래스 내부에서도 사용 가능!
	void Output(T a, T1 b)
	{
		cout << a << endl;
		cout << b << endl;
	}
};

template <typename T> // 클래스 자체적으로도 사용 가능!
class CTemplate1
{
public:
	CTemplate1()
	{
		cout << "Template1 class Type : " << typeid(T).name() << endl;
	}
	
	~CTemplate1()
	{
	}
	
private:
	T m_Data;
	
public:
	void Output()
	{
		cout << typeid(T).name() << endl;
		cout << m_Data << endl;
	}
};

int main()
{
	OutputType<int>(); // T 부분에 타입을 가변적으로 지정
	OutputType<float>();
	OutputType<STUDENT>(); // 클래스
	OutputType<CCar>(); // 구조체
	OutputType<TEST>(); // 열거체
	
	OutputData(10); // 이런 식으로 인자를 받아서 타입을 가변적으로 만들 수 있음!
	OutputData(3.1);
	OutputData(382.383f);
	OutputData("a");
	OutputData("ㅋㅋㅋ");
	
	CTemplate tem;
	
	tem.Output(10, 3.14f); // 템플릿을 이용해서 인자 타입을 가변적으로 설정할 수 있음!
	
	CTemplate1<int> tem1;
	
	tem1.Output();
	
	CTemplate1<CTemplate> tem2; // 클래스 타입을 받음
	
	return 0;
}
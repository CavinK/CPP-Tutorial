#include <iostream>
#include <cstring>

using namespace std;

/*
객체(object): 모든 사물을 의미한다. 
C++에서 객체를 의미하는 것은 각 변수들도 객체로 취급할 수 있다.
하지만 객체지향 프로그래밍을 지원하기 위해 제공되는 수단은 class이다.
class는 객체가 아니라, 객체를 만들기 위한 틀이다. <- class는 사용자 정의 타입일 뿐!

객체지향 프로그래밍(OOP): 객체들의 관계를 설정해줘서 부품을 조립하듯이, 객체들을 조립하여 완성된 프로그램을 만들어 나가는 방식이다.

클래스 선언 방법: class 클래스명 {}; 의 형태로 선언한다.
코드 블럭 안에 멤버 변수를 넣어줄 수 있다.
단, 함수도 멤버로 만들 수 있다. <- cf. 구조체: C에서는 변수만 멤버로 포함시킬 수 있음, C++에서는 함수도 멤버로 넣어줄 수 있음

클래스의 4가지 속성
캡슐화(encapsulation): 클래스 안에 속하는 여러 변수 혹은 함수를 하나의 클래스로 묶어주는 기능을 말한다.
은닉화(abstraction): 클래스 안에 속하는 변수 혹은 함수를 내가 원하는 부분만 외부에 공개하고, 외부에 공개하지 않을 수 있다.
	- public: 클래스 내부와 외부에서 모두 접근 가능한 방법이다. <- 구조체: default로 public
	- protected: 클래스 외부에서는 접근이 불가능하고, 자기 자신 내부나 자식 클래스 내부에서는 접근이 가능한 방법이다. <- 상속과 연관!
	- private: 자기 자긴 내부에서만 접근이 가능하고, 외부나 자식 내부에서는 접근이 불가능한 방법이다. <- 클래스: default로 private
상속성(inheritance): 클래스는 클래스와 클래스 간에 부모, 자식 관계를 형성할 수 있다.
자식 클래스는 부모 클래스의 멤버를 물려 받아 자신의 것처럼 사용할 수 있다.
단, private으로 되어 있는 멤버에는 접근이 불가능하다.
다형성(polymorphism): 부모 자식 관계로 상속 관계가 형성되어 있는 클래스 간에 서로 형 변환(type-casting)이 가능한 성질을 말한다.



생성자와 소멸자 <- 클래스에서 사용하는 특수한 함수!
생성자: 어떤 클래스를 이용해서 객체를 생성할 때 자동으로 호출되는 함수이다.
객체 생성 시 호출되는 함수이기 때문에 객체의 멤버 변수를 초기화할 때 유용하게 사용할 수 있다.
생성자를 만들어주지 않을 경우, 내부적으로 기본 생성자가 제공이 되어서 기본 생성자를 자동으로 호출해주게 된다.
클래스명()
{
}
의 형태로 선언된다.

소멸자: 어떤 클래스를 이용해서 생성한 객체가 메모리에서 해제될 때, 자동으로 호출되는 함수이다.
객체를 사용하고 난 뒤에 마무리 작업을 해줄 때 유용하게 사용할 수 있다.
~클래스명()
{
}
의 형태로 선언된다.
*/
class CTracer
{
public: // private으로 해주면 생성자, 소멸자 호출이 불가능!
	// 생성자 <- 함수라서 오버로딩 가능!
	CTracer()
	{
		cout << "Tracer 생성자" << endl; // 객체가 생성되는 순간 실행됨
		strcpy(m_strName, "트레이서");
	}
	
	CTracer(const char* pName) // https://stackoverflow.com/q/20944784
	{
		strcpy(m_strName, pName); // 이름을 세팅하도록 오버로딩 => 객체 생성할 때 인자를 받을 수 있음!
		
		cout << "Name 생성자" << endl;
	}
	
	// Initialiser1
	CTracer(const char* pName, int iFlash)
	{
		strcpy(m_strName, pName);
		m_iFlash = iFlash; // 인자값 선언 후 초기화 <- int a; a=10;
		
		cout << "Name, Flash 생성자" << endl;
	}
	
	// Initialiser2
	CTracer(const char* pName, int iFlash, int iBack):
		m_iBack(iBack), // 선언과 동시에 초기화 <- int b=10;
		m_iFlash(iFlash)
	{
		strcpy(m_strName, pName);
			
		cout << "Name, Flash, Back 생성자" << endl;
	}

	// 소멸자
	~CTracer() 
	{
		cout << "Tracer 소멸자" << endl; // 멤버 함수가 종료되는 순간 실행됨(메모리 해제)
	}
	
	// 클래스 멤버 변수를 선언할 때는 m_를 붙여준다.
	char m_strName[32]; // 기본이 private!
	
public: // public 키워드 아래에 있는 멤버는 모두 외부에서 접근이 가능하다.
	int m_iAttack;
	int m_iHP;

private: // private으로 설정하는 게 bug를 잡아내기 편함!
	int m_iFlash;

private: // 이렇게 똑같은 키워드를 여러 개 사용 가능!
	int m_iBack;

public:
	void Output() // 멤버 함수
	{
		cout << "Tracer Output" << endl;
		cout << "Name: " << m_strName << endl;
	}
};

int main()
{
	CTracer tr1("Cavin"); // 객체 생성 => 생성함과 동시에 생성자가 자동으로 호출됨!(내부적으로 default 생성자를 가지고 있음)
	CTracer tr2("Cavin", 3);
	CTracer tr3("Cavin", 3, 1);
	
	// main() 함수 안은 클래스 외부이기 때문에 public으로 설정되어 있는 멤버에만 접근이 가능하다.
	// tr1.m_iAttack
	tr1.Output();
	
	return 0;
}
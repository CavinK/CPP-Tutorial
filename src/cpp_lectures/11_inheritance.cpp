#include <iostream>

using namespace std;

/*
상속: 클래스는 서로 간에 부모과 자식 관계를 형성할 수 있다.
자식 클래스는 부모 클래스의 멤버들을 사용할 수 있다.

부모 클래스에서 public이나 protected로 되어 있는 멤버들은 사용 가능하지만,
private으로 되어 있는 멤버는 자식에서도 사용이 불가능하다.

상속의 형태: public, private 상속이 있다.

다형성: 상속 관계에 있는 클래스 간에 서로 형 변환이 가능한 성질을 말한다.

가상 함수: 오버라이딩 이라고도 부른다.
함수를 재정의 하는 기능이다.
멤버 함수 앞에 virtual 키워드를 붙이면, 해당 함수는 가상 함수가 된다.
만약 CParent 클래스에 virtual void Output() 함수가 있다면,
자식 클래스에서는 이 가상 함수를 재정의할 수 있다.
재정의는 함수 이름과 인자가 완전히 똑같아야 한다. <- cf. 오버로딩

가상 함수를 가지고 있는 클래스는 내부적으로 가상 함수 테이블이라는 것을 생성한다.
가상 함수 테이블은 가상 함수들의 메모리 주소를 저장하는 테이블이다.

만약 CParent의 Output이 가상 함수이고, CChild 클래스에 Output을 재정의 한다면,
그런 뒤 CChild 객체를 생성하면 가상 함수 테이블에는 CChild 클래스의 Output 함수 주소가 올라가게 된다. <- 각 함수의 메모리 주소는 1개!

만약 CParent 객체를 생성한다면, CParent의 Output 주소가 올라가게 된다.

그래서 Output 함수, 즉 가상 함수를 호출하게 되면 먼저 가상 함수 테이블을 참조해서 메모리 주소를 확인한다.
가상 함수 테이블에 CChild의 Output 주소가 들어가 있다면, 그 주소의 함수를 호출해주는 개념이다.
-> 테이블 한 번 참조 => 일반 함수를 호출하는 것보다 좀 느림!

소멸자도 가상 함수로 만들 수 있다.
부모의 소멸자는 가상 함수로 만들어주자.
*/

class CParent
{
public:
	CParent()
	{
		cout << "CParent 생성자" << endl;
	}
	
	virtual ~CParent() // 부모의 소멸자는 가상 함수로!
	{
		cout << "CParent 소멸자" << endl;
	}
	
public:
	int m_iA;
	
protected:
	int m_iB;
	
private:
	int m_iC;
	
public:
	virtual void Output()
	{
		cout << "Parent Output Function" << endl;
	}
	
	// 순수가상함수: 가상 함수 뒤에 = 0 을 붙여주면, 
	// 해당 가상함수는 순수가상함수가 된다.
	// 순수가상함수는 구현 부분이 존재하지 않는다.
	// 순수가상함수를 가지고 있는 클래스를 추상 클래스라고 부른다.
	// 추상 클래스는 인스턴스(객체) 생성이 불가능하다.
	// 순수가상함수는 자식에서 반드시 재정의 해야 한다.
	// 왜냐하면 순수가상함수는 정의 부분이 없기 때문에 반드시 자식에서 재정의해서 사용할 목적으로 만들어주는 함수이기 때문이다.
	virtual void OutputPure() = 0; // 순수가상함수 <- 순수하게 구현 부분이 없는 함수!
};

class CChild : public CParent // public 상속
{
public:
	CChild()
	{
		m_iB = 200; // parent의 protected 멤버
		// m_iC는 private이기 때문에 자식 내부에서도 접근이 불가능하다.
		// m_iC = 300; // parent의 private 멤버 <- 에러! <- private은 자신의 내부에서만 접근 가능!
		cout << "CChild 생성자" << endl;
	}
	
	virtual ~CChild()
	{
		cout << "CChild 소멸자" << endl;
	}
	
protected:
	int m_iD;
	
public:
	void ChildOutput()
	{
		cout << "Child Output Function" << endl;
	}
	
	virtual void Output() // 부모 클래스의 가상 함수를 재정의 <- 오버라이딩
	{
		CParent::Output(); // 자식 클래스에서 부모 클래스의 함수 호출 가능!
		cout << "Child Output Function" << endl;
	}
	
	virtual void OutputPure()
	{
		
	}
};

class CChild1 : private CParent // private 상속
{
public:
	CChild1()
	{
		m_iA = 100; // main() 함수에서는 멤버 변수 호출이 불가능하지만, 생성자에서는 가능!
		m_iB = 200;
		cout << "CChild1 생성자" << endl;
	}
	
	~CChild1()
	{
		cout << "CChild1 소멸자" << endl;
	}
	
private:
	int m_iD;
	
public:
	virtual void OutputPure()
	{
		
	}
};

class CChildChild : public CChild
{
public:
	CChildChild()
	{
		m_iD = 500;
		cout << "CChildChild 생성자" << endl;
	}
	
	~CChildChild()
	{
		cout << "CChildChild 소멸자" << endl;
	}
	
private:
	int m_iE;
};

int main()
{
	/*
	상속 관계에서의 생성자 호출 순서: 부모 -> 자식 순으로 호출된다.
	상속 관계에서의 소멸자 호출 순서: 자식 -> 부모 순으로 호출된다.
	
	생성자, 소멸자 호출 순서
	생성자: 부모 클래스가 먼저 호출되고 그 다음에 자식 클래스가 호출됨
	소멸자: 자식 클래스가 먼저 호출되고 그 다음에 부모 클래스가 호출됨
	*/
	
	// CParent parent;
	// CChild child;
	// CChild1 child1;
	// CChildChild childchild;
	
	// parent.m_iA = 100;
	
	// child.m_iA = 200;
	
	// CChild1 클래스는 CParent를 private 상속을 하고 있으므로
	// CParent에 public으로 설정되어 있는 멤버들도 외부에서는 접근이 불가능하다.
	// child1.m_iA = 300; // 에러! <- private 상속
	// child1.Output(); // 에러! <- private 상속
	
	// 다형성
	// CChild 클래스는 CParent 클래스를 상속받고 있다.
	// new CChild를 하게 되면 CChild 객체 하나를 생성해주고 그 메모리 주소를 반환해준다.
	// 그런데 아래에서는 CParent * 타입 변수에 이 반환된 주소를 대입해주고 있다.
	// 부모 포인터 타입에 CChild 객체의 메모리 주소를 넣을 수 있는 이유는 상속 관계에 있기 때문이다.
	// 자식 메모리 주소를 부모 포인터 타입으로 형 변환된 것이기 때문이다.
	// 이런 형 변환을 업캐스팅이라고 한다.
	// 자식 -> 부모 타입 형 변환: 업캐스팅
	// 부모 -> 자식 타입 형 변환: 다운캐스팅 <- 주의!
	CParent* pParent = new CChild; // CChild 클래스의 객체를 생성했지만, 근본적으로는 CParent 타입 => delete할 때 CParent 소멸자만 호출!
	// CParent* pParent1 = new CChild1;
	// CParent* pParent2 = new CChildChild;
	CChild1 child1; // 순수가상함수의 경우 모든 자식 클래스에 재정의 해줘야 함!
	// CParent parent; // 추상 클래스는 객체 생성이 안 됨! <- 포인터(CParent*)는 생성이 가능!!
	// 포인터는 그냥 메모리 주소를 담은 변수 <- 공통된 인터페이스 제공
	
	// 인터페이스
	// CParent* pParentArr[2] = {};
	
	// pParentArr[0] = new CChild;
	// pParentArr[1] = new CChildChild; // 배열을 이용해서 상속 관계에 있는 모든 클래스를 넣을 수 있음!
	
	// 아래 두 클래스는 모두 CParent 클래스를 상속 받고 있다.
	// 그러므로 pParent를 두 타입 모두 다운캐스팅 가능하다.
	// 그런데 pParent는 CChild로 할당한 객체이다.
	// 이 객체를 CChild1 타입으로 다운캐스팅 하여 넣어주게 되면,
	// 이 객체를 사용할 때 문제가 발생할 수 있다.
	// 왜냐하면 애초에 생성한 객체가 아닌 다른 타입으로 변환됐기 때문이다.
	CChild* pChild = (CChild*)pParent; // 이 형 변환은 문제 없음
	// CChild1* pChild1 = (CChild1*)pParent; // 에러!
	// ex. CChild가 30바이트 짜리 클래스인데 CChild1가 500바이트 짜리 클래스면 없는 부분을 참조하게 될 수도 있음!
	
	// pParent로는 CChild 클래스에 있는 ChildOutput 함수에 접근할 수 없다
	// 왜냐하면 pParent는 CParent 포인터 타입이기 때문에 자식 멤버에 접근이 불가능하기 때문이다.
	// 만약 접근하고 싶다면 형 변환해야 한다.
	// pParent->ChildOutput(); // 에러!
	// ((CChild*)pParent)->ChildOutput();
	pParent->Output(); // 자식 클래스에서 재정의된 함수가 호출됨 <- 재정의된 함수가 없으면 부모 클래스의 함수가 호출됨!
	// 자식 클래스에 재정의된 함수가 있으면 그 함수 메모리가 가상 함수 테이블에 올라가고
	// 재정의된 함수가 없으면 부모 클래스의 함수 메모리 주소가 가상 함수 테이블에 올라감!!
	pParent->CParent::Output(); // 명시적으로 클래스 지정 => 재정의된 함수가 있어도 해당 클래스의 함수 호출
	
	// 현재 delete를 하게 되면 CChild 소멸자 -> CParent 소멸자가 호출되어야 하는데
	// 지금은 CParent 소멸자만 호출된다.
	// 왜냐하면 근본적으로 pParent는 CParent 포인터 타입이다.
	// CParent 포인터 타입이기 때문에 CChild 소멸자가 호출될 수 없다.
	delete pParent;
	// delete pChild; // 이 경우에는 CChild 포인터이므로 CChild 소멸자가 호출됨!
	// delete pParent2;
	
	for (int i = 0; i < 2; ++i)
	{
		// delete pParentArr[i];
	}
	
	return 0;
}
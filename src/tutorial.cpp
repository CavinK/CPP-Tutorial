#include <iostream>

using namespace std;

/*
상속: 클래스는 서로 간에 부모과 자식 관계를 형성할 수 있다.
자식 클래스는 부모 클래스의 멤버들을 사용할 수 있다.

부모 클래스에서 public이나 protected로 되어 있는 멤버들은 사용 가능하지만,
private으로 되어 있는 멤버는 자식에서도 사용이 불가능하다.

상속의 형태: public, private 상속이 있다.
*/

class CParent
{
public:
	CParent()
	{
		cout << "CParent 생성자" << endl;
	}
	
	~CParent()
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
	void Output()
	{
		cout << "A: " << m_iA << endl;
		cout << "B: " << m_iB << endl;
		cout << "C: " << m_iC << endl;
	}
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
	
	~CChild()
	{
		cout << "CChild 소멸자" << endl;
	}
	
protected:
	int m_iD;
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
	CParent parent;
	CChild child;
	CChild1 child1;
	CChildChild childchild;
	
	parent.m_iA = 100;
	
	child.m_iA = 200;
	
	// CChild1 클래스는 CParent를 private 상속을 하고 있으므로
	// CParent에 public으로 설정되어 있는 멤버들도 외부에서는 접근이 불가능하다.
	// child1.m_iA = 300; // 에러! <- private 상속
	// child1.Output(); // 에러! <- private 상속
	
	return 0;
}
#pragma once

// 링크드 리스트에 template를 사용하면 모든 타입을 저장하는 게 가능!
template <typename T>
class CListNode
{
	// 생성자와 소멸자를 private하게 되면 외부에서 객체를 생성하고 객체를 해제할 수 없다.
	// 생성자는 객체를 생성할 때 자동으로 호출이 되는 함수인데
	// private으로 되면 객체를 생성하면서 호출 시 접근이 불가능하다.
private: // 외부에서 접근이 불가능 but CLinkedList 클래스에서만 접근이 가능하게 만듬!
	CListNode() :
		m_pNext(NULL),
		m_pPrev(NULL)
	{
	}
	
	~CListNode()
	{
	}
	
private:
	// friend: 친구로 만들어준다.
	// friend로 지정해준 클래스에서 이 클래스의 private나 protected에 접근이 가능해준다.
	// 일반 클래스는 friend 라인만 적으면 되지만
	// template 클래스의 경우, 아래처럼 template를 지정해 주어야 한다.
	template <typename T1> // error: declaration of template parameter 'T' shadows template parameter
	friend class CLinkedList;
	template <typename T2>
	friend class CListIterator;
	template <typename T3>
	friend class CListReverseIterator;
	
private:
	T m_Data;
	CListNode<T>* m_pNext;
	CListNode<T>* m_pPrev;
};

// 반복자 클래스: 리스트의 노드를 반복해서 순회할 수 있는 기능을 제공하는 클래스이다.
template <typename T>
class CListIterator
{
public:
	CListIterator()
	{
	}
	
	~CListIterator()
	{
	}
	
private:
	template <typename T1>
	friend class CLinkedList;
	
private:
	typedef CListNode<T> NODE;
	typedef CListNode<T>* PNODE;
	
private:
	PNODE m_pNode;
	
public: // main 함수에서 리더 클래스 호출할 때 사용할 연산자 정의
	bool operator ==(const CListIterator<T>& iter)
	{
		return m_pNode == iter.m_pNode;
	}
	
	bool operator !=(const CListIterator<T>& iter)
	{
		return m_pNode != iter.m_pNode;
	}
	
	void operator ++()
	{
		m_pNode = m_pNode->m_pNext;
	}
	
	void operator --()
	{
		m_pNode = m_pNode->m_pPrev;
	}
	
	T operator *() // 역참조
	{
		return m_pNode->m_Data;
	}
};

// List Reverse Iterator
template <typename T>
class CListReverseIterator
{
public:
	CListReverseIterator()
	{
	}
	
	~CListReverseIterator()
	{
	}

private:
	template <typename T2>
	friend class CLinkedList;
	
private:
	typedef CListNode<T> NODE;
	typedef CListNode<T>* PNODE;
	
private:
	PNODE m_pNode;
	
public:
	bool operator ==(const CListReverseIterator<T>& iter) // 일반 변수는 그냥 받아도 무방하고, 클래스는 참조로 받는 게 빠름!(최적화)
	{
		return m_pNode == iter.m_pNode;
	}
	
	bool operator !=(const CListReverseIterator<T>& iter)
	{
		return m_pNode != iter.m_pNode;
	}
	
	void operator ++()
	{
		m_pNode = m_pNode->m_pPrev; // reverse!
	}
	
	void operator --()
	{
		m_pNode = m_pNode->m_pNext; // reverse!
	}
	
	T operator *()
	{
		return m_pNode->m_Data;
	}
};

template <typename T>
class CLinkedList
{
public:
	CLinkedList()
	{
		m_pBegin = new NODE;
		m_pEnd = new NODE;
		
		m_pBegin->m_pNext = m_pEnd;
		m_pEnd->m_pPrev = m_pBegin;
		
		m_iSize = 0;
	}
	
	~CLinkedList()
	{
		clear();
		delete m_pBegin;
		delete m_pEnd;
		m_iSize = 0;
	}
	
private:
	typedef CListNode<T> NODE; // CListNode<T> 타입을 NODE로도 쓸 수 있게 하는 거!
	typedef CListNode<T>* PNODE;
	
public:
	typedef CListIterator<T> iterator; // inner class: 클래스 안에 있는 클래스
	typedef CListReverseIterator<T> reverse_iterator;
	
private:
	PNODE m_pBegin;
	PNODE m_pEnd;
	unsigned int m_iSize;
	
public:
	// 레퍼런스는 참조하는 대상의 값을 변경할 수 있다.
	// 그런데 const를 붙여주면 참조하는 대상의 값을 변경할 수 없다.
	void push_back(const T& data) // 100바이트 복사(void push_back(T))보다 4바이트 참조(void push_back(const T&))가 더 빠름!
	{
		PNODE pNode = new NODE;
		
		pNode->m_Data = data;
		
		// End의 이전 노드가 가장 마지막 노드이다.
		PNODE pPrev = m_pEnd->m_pPrev;
		
		// 연결해준다.
		pPrev->m_pNext = pNode;
		pNode->m_pPrev = pPrev;
		
		pNode->m_pNext = m_pEnd;
		m_pEnd->m_pPrev = pNode;
		
		++m_iSize;
	}
	
	void push_front(const T& data)
	{
		PNODE pNode = new NODE;
		
		pNode->m_Data = data;
		
		// Begin의 다음 노드는 가장 첫번째 노드이다.
		PNODE pFirst = m_pBegin->m_pNext;
		
		pFirst->m_pPrev = pNode;
		pNode->m_pNext = pFirst;
		
		pNode->m_pPrev = m_pBegin;
		m_pBegin->m_pNext = pNode;
		
		++m_iSize;
	}
	
	// 멤버 함수 뒤에 const를 붙여주면 이 함수 내에서 멤버 변수의 값을 변경할 수 없다.
	// get 함수의 경우 뒤에 const를 많이 붙여줌!
	unsigned int size() const
	{
		// m_iSize = 10; // 이게 안 됨!(const)
		return m_iSize;
	}
	
	bool empty() const
	{
		return m_iSize == 0;
	}
	
	void clear()
	{
		// 첫번째 노드를 얻어온다.
		PNODE pNode = m_pBegin->m_pNext;
		
		// pNode가 End가 되면 반복을 종료한다.
		// 이렇게 해서 Begin과 End를 제외한 모든 노드를 삭제한다.
		while (pNode != m_pEnd)
		{
			PNODE pNext = pNode->m_pNext;
			delete pNode;
			pNode = pNext;
		}
		
		m_pBegin->m_pNext = m_pEnd;
		m_pEnd->m_pPrev = m_pBegin;
		m_iSize = 0;
	}
	
	iterator begin()
	{
		iterator iter;
		iter.m_pNode = m_pBegin->m_pNext;
		return iter;
	}
	
	iterator end()
	{
		iterator iter;
		iter.m_pNode = m_pEnd;
		return iter;
	}
	
	reverse_iterator rbegin()
	{
		reverse_iterator iter;
		iter.m_pNode = m_pEnd->m_pPrev;
		return iter;
	}
	
	reverse_iterator rend()
	{
		reverse_iterator iter;
		iter.m_pNode = m_pBegin;
		return iter;
	}
};
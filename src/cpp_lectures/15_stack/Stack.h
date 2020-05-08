#pragma once

// Stack을 만드는 방법
// 1. 배열을 이용하는 방법
// 2. 리스트를 이용하는 방법

// Stack: First In Last Out <- 입구가 하나!
// => 마지막 노드만 알고 있으면 됨!!(Single Linked List의 형태)

template <typename T>
class CStackNode
{
private:
	CStackNode() :
		m_pNext(NULL) // 다음 노드의 초기 값은 NULL
	{
	}
	
	~CStackNode()
	{
	}
	
private:
	template <typename T1>
	friend class CStack;
	
private:
	T m_Data;
	CStackNode<T>* m_pNext;
};

template <typename T>
class CStack
{
public:
	CStack()
	{
		m_pBegin = new NODE;
		m_pEnd = new NODE;
		
		m_pBegin->m_pNext = m_pEnd;
		
		m_iSize = 0;
	}
	
	~CStack()
	{
		PNODE pNode = m_pBegin;
		
		while (pNode)
		{
			PNODE pNext = pNode->m_pNext;
			delete pNode; // 소멸자에서 모든 노드를 다 지움
			pNode = pNext;
		}
	}
	
private:
	typedef CStackNode<T> NODE;
	typedef CStackNode<T>* PNODE;
	
private:
	PNODE m_pBegin;
	PNODE m_pEnd;
	unsigned int m_iSize;
	
public:
	void push(const T& data) // push back 기능 <- stack에는 입구가 하나 밖에 없음!
	{
		// 노드 생성
		PNODE pNode = new NODE;
		pNode->m_Data = data;
		
		// 그 노드가 begin 다음의 노드(시작 시점에서는 end)에 연결되게 함
		PNODE pNext = m_pBegin->m_pNext;
		pNode->m_pNext = pNext;
		
		// begin 다음에 생성된 노드를 연결(중간에 끼워넣음!)
		m_pBegin->m_pNext = pNode;
		
		++m_iSize;
	}
	
	T pop()
	{
		if (empty())
			return 0;
		
		// 가져올 노드는 begin의 다음 노드이다.
		PNODE pNode = m_pBegin->m_pNext;
		
		// 가져올 노드를 지워주려면, begin과 가져올 노드의 다음 노드를 연결해 주어야 한다.
		PNODE pNext = pNode->m_pNext;
		
		T data = pNode->m_Data; // begin의 다음 노드의 데이터
		
		delete pNode;
		
		m_pBegin->m_pNext = pNext; // begin과 가져올 노드의 다음 노드와 연결
		
		--m_iSize;
		
		return data;
	}
	
	T top()
	{
		if (empty())
			return 0;
		
		return m_pBegin->m_pNext->m_Data; // 가장 위의 노드의 데이터를 리턴만 하는 거
	}
	
	bool empty()
	{
		return m_iSize == 0;
	}
};
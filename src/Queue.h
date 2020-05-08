#pragma once

// Queue
// First In First Out <- 새로운 노드를 End 이전에 넣음!
// 배열 기반이나 리스트 기반으로 만들 수 있음 <- 여기서도 Single Linked List 사용!

template <typename T>
class CQueueNode
{
private:
	CQueueNode() :
		m_pNext(NULL),
		m_pPrev(NULL) // Double Linked List
	{
	}
	
	~CQueueNode()
	{
	}
	
private:
	template <typename T1>
	friend class CQueue;
	
private:
	T m_Data;
	CQueueNode<T>* m_pNext;
	CQueueNode<T>* m_pPrev; // Double Linked List
};

template <typename T>
class CQueue
{
public:
	CQueue()
	{
		m_pBegin = new NODE;
		m_pEnd = new NODE;
		
		m_pBegin->m_pNext = m_pEnd;
		m_pEnd->m_pPrev = m_pBegin;
		
		m_iSize = 0;
	}
	
	~CQueue()
	{
	}
	
private:
	typedef CQueueNode<T> NODE;
	typedef CQueueNode<T>* PNODE;
	
private:
	PNODE m_pBegin;
	PNODE m_pEnd;
	unsigned int m_iSize;
	
public:
	void push(const T& data) // push back
	{
		// 노드 생성
		PNODE pNode = new NODE;
		pNode->m_Data = data;
		
		// 새로운 노드를 end 앞에 끼워넣음! <- cf. stack: begin 뒤에 끼워넣음
		PNODE pPrev = m_pEnd->m_pPrev;
		
		pPrev->m_pNext = pNode;
		pNode->m_pPrev = pPrev;
		
		pNode->m_pNext = m_pEnd;
		m_pEnd->m_pPrev = pNode;
		
		++m_iSize;
	}
	
	T pop()
	{
		if (empty())
			return 0;
		
		PNODE pNode = m_pBegin->m_pNext; // begin 다음에 있는 노드를 pop <- First In First Out
		
		T data = pNode->m_Data;
		
		// begin의 다음 노드를 지우므로 begin과 지울 노드의 다음 노드를 서로 연결해준다.
		m_pBegin->m_pNext = pNode->m_pNext;
		pNode->m_pNext->m_pPrev = m_pBegin;
		
		delete pNode;
		--m_iSize;
		
		return data;
	}
	
	bool empty()
	{
		return m_iSize == 0;
	}
};



// Circle Queue
// 정해진 배열 안에서 꼬리에 꼬리를 물면서 노드를 추가, 삭제
// 배열 방식 사용!

template <typename T, int SIZE = 100> // T는 가변적, SIZE는 int로 고정하고 "상수"로 할당 <- compile 단계에서 정해지게 만듬
class CCircleQueue
{
public:
	CCircleQueue()
	{
		m_iSize = 0;
		m_iHead = 0;
		m_iTail = 0;
	}
	
	~CCircleQueue()
	{
	}
	
private:
	T m_Data[SIZE + 1]; // SIZE는 100이지만, head와 tail이 만나는 부분은 남겨둬야 함 => 실제 저장 공간은 99개 => +1을 해줌!
	unsigned int m_iSize;
	unsigned int m_iHead;
	unsigned int m_iTail;
	
public:
	void push(const T& data)
	{
		if (full())
			return;
		
		int idx = (m_iTail + 1) % (SIZE + 1); // 101에 101을 나눈 나머지는 0 => 0번 인덱스로 되돌아감!
		
		m_Data[idx] = data;
		
		m_iTail = idx;
		
		++m_iSize;
	}
	
	T pop()
	{
		if (empty())
			return 0;
		
		int idx = (m_iHead + 1) % (SIZE + 1);
		
		T data = m_Data[idx];
		
		m_iHead = idx;
		--m_iSize;
		
		return data;
	}
	
	bool full()
	{
		return m_iSize == SIZE;
	}
	
	bool empty()
	{
		return m_iSize == 0;
	}
};
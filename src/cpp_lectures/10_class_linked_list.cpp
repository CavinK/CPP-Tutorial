#include <iostream>
#include <climits>

using namespace std;

// 노드
class CListNode
{
public:
	CListNode() : 
		// 초기화
		m_pNext(NULL),
		m_pPrev(NULL)
	{
	}
	~CListNode()
	{
	}
	
public:
	int m_iData;
	CListNode* m_pNext;
	CListNode* m_pPrev;
};

// 리스트
class CList
{
public:
	CList()
	{
		m_pBegin = new CListNode; // double linked list!
		m_pEnd = new CListNode;
		
		m_pBegin->m_pNext = m_pEnd; // pBegin과 pEnd가 서로 연결
		m_pEnd->m_pPrev = m_pBegin;
		
		m_iSize = 0;
	}
	~CList()
	{
		// 소멸자를 이용해 초기화 해서 memory leak 방지!
		clear();
		delete m_pBegin;
		delete m_pEnd;
	}
	
private:
	CListNode* m_pBegin;
	CListNode* m_pEnd;
	int m_iSize;
	
public:
	void push_back(int iData) // 뒤에다 추가
	{
		CListNode* pNode = new CListNode;
		
		pNode->m_iData = iData;
		
		CListNode* pPrev = m_pEnd->m_pPrev;
		
		pPrev->m_pNext = pNode;
		pNode->m_pPrev = pPrev;
		
		pNode->m_pNext = m_pEnd;
		m_pEnd->m_pPrev = pNode;
		
		++m_iSize;
	}
	
	int pop_back()
	{
		CListNode* pPrev = m_pEnd->m_pPrev;
		
		if (pPrev == m_pBegin) // pBegin과 pEnd 사이에 노드가 없다는 뜻
			return INT_MAX;
		
		int iData = pPrev->m_iData;
		
		CListNode* pPrevP = pPrev->m_pPrev;
		
		pPrevP->m_pNext = m_pEnd;
		m_pEnd->m_pPrev = pPrevP;
		
		--m_iSize;
		
		delete pPrev;
		
		return iData;
	}
	
	bool empty()
	{
		return m_iSize == 0;
	}
	
	void clear()
	{
		CListNode* pNode = m_pBegin->m_pNext;
		
		while (pNode != m_pEnd) // pEnd 이전까지 삭제
		{
			CListNode* pNext = pNode->m_pNext;
			delete pNode;
			pNode = pNext;
		}
		
		m_pBegin->m_pNext = m_pEnd;
		m_pEnd->m_pPrev = m_pBegin;
		
		m_iSize = 0;
	}
};

int main()
{
	CList list;
	
	for (int i = 0; i < 100; ++i)
	{
		list.push_back(i);
	}
	
	while (!list.empty())
	{
		cout << list.pop_back() << endl;
	}
	
	return 0;
}
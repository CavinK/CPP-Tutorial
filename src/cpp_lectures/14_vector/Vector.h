#pragma once

#include <cstring>

// 벡터 <- 동적 배열!

template <typename T>
class CVectorNode
{
private: // private 생성자, 소멸자 => friend class!
	CVectorNode()
	{
	}
	
	~CVectorNode()
	{
	}
	
private:
	template <typename T1>
	friend class CVector;
	
private:
	T m_Data; // 데이터
	int m_iIndex; // 인덱스
};

template <typename T>
class CVector
{
public:
	CVector()
	{
		m_iSize = 0;
		m_iCapacity = 2; // 생성자에서 설정해놓음 => 자동으로 늘어남
		
		m_pArray = new NODE[m_iCapacity + 2]; // 동적 배열 할당 // 2: Begin, End
	}
	
	CVector(int iSize) // 생성자를 통해서 공간 예약이 가능하게 만들어 놓음!
	{
		m_pArray = new NODE[iSize + 2];
		m_iCapacity = iSize;
		m_iSize = 0;
		// reserve(iSize);
	}
	
	~CVector()
	{
		delete[] m_pArray;
	}
	
private:
	typedef CVectorNode<T> NODE;
	typedef CVectorNode<T>* PNODE;
	
private:
	PNODE m_pArray;
	unsigned int m_iSize; // 추가된 배열 개수
	unsigned int m_iCapacity; // 전체 배열 개수
	
public:
	void push_back(const T& data) // push_front는 안 만듬 <- 벡터에서 맨 앞에 추가하려면 기존 것들은 다 한 칸 씩 뒤로 미뤄야 함 => 느려짐!
	{
		if (full())
			resize(m_iSize * 2);
		
		m_pArray[m_iSize + 1].m_Data = data;
		// 0번은 begin이다.
		// 그런데 실제 1번 인덱스부터 노드가 추가되는데 처음 추가된 노드는 0번부터 인덱스를 주도록 한다.
		m_pArray[m_iSize + 1].m_iIndex = m_iSize;
		++m_iSize;
	}
	
	void resize(int iSize) // 이 부분이 문제? <- 성능 저하가 심함 => 해결!
	{
		// +2 를 해주는 이유는 begin과 end를 포함시켜서 생성하기 위해서 이다.
		PNODE pArray = new NODE[iSize + 2];
		
		// 위에서 2배 만큼 공간을 새로 할당하고, 기존에 있는 노드의 데이터를 새로 할당한 공간에 복사해준다.
		// 메모리 주소에 +1 을 해준 이유는 1번 인덱스부터 시작이기 때문에 여기부터 복사를 해주기 위해서 +1 을 해주었다.
		memcpy(pArray + 1, m_pArray + 1, sizeof(NODE) * m_iSize); // m_pArray: 기존 내용 => pArray에 복사
		
		// 기존 노드를 삭제한다.
		delete[] m_pArray;
		
		m_pArray = pArray; // 오타!
		
		m_iCapacity = iSize;
	}
	
	void clear()
	{
		delete[] m_pArray;
		m_iSize = 0;
		m_iCapacity = 2; // begin & end
		m_pArray = new NODE[m_iCapacity + 2];
	}
	
	bool full()
	{
		return m_iSize == m_iCapacity; // 트리가 꽉 찼다는 뜻
	}
	
	bool empty()
	{
		return m_iSize == 0;
	}
	
	unsigned int size() const
	{
		return m_iSize;
	}
	
	unsigned int capacity() const
	{
		return m_iCapacity;
	}
	
	T operator [](int idx) // 인덱스 조회도 연산자의 한 종류!
	{
		return m_pArray[idx + 1].m_Data; // 데이터는 1부터 시작!
	}
	
	void reserve(int iSize) // 공간을 미리 예약
	{
		delete[] m_pArray;
		m_pArray = new NODE[iSize + 2];
		
		m_iCapacity = iSize;
		m_iSize = 0;
	}
};
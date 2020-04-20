// 헤더 파일
// 그 함수의 선언, 정의가 들어감!

// #pragma once: 이 헤더파일을 딱 1번만 포함시키겠다 라는 의미이다.
#pragma once

#include <iostream>

using namespace std;

enum OUTPUT_TYPE
{
	OT_NONE,
	OT_OUTPUT, // 정방향 출력
	OT_INVERSE // 역방향 출력
};

// 정렬 기준 <- Sort()
enum SORT_TYPE
{
	ST_NONE,
	ST_NUMBER,
	ST_AVG
};

// 오름차순 or 내림차순
enum SORT_OPTION
{
	SO_NONE,
	SO_CRIVE,
	SO_DESCRIVE
};

// 헤더 파일에는 보통 함수 선언 부분을 만들어준다
#define NAME_SIZE 32

typedef struct _tagStudent
{
	char strName[NAME_SIZE];
	int iNumber;
	int iKor;
	int iEng;
	int iMath;
	int iTotal;
	float fAvg;
}STUDENT, *PSTUDENT;

typedef struct _tagNode
{
	STUDENT tStudent;
	_tagNode* pNext;
	_tagNode* pPrev; // 더블링크드리스트는 이전 노드 주소에 대한 정보도 필요!
}NODE, *PNODE;

typedef struct _tagList
{
	// pStart와 pEnd는 명시적으로 처음과 끝을 의미하도록 만든다. <- 노드가 추가할 때마다 일일이 정적 할당하는 게 아니라, 아예 처음과 끝을 고정!
	// 실제 데이터를 저장하는 노드는 아니다.
	// 실제 데이터를 저장하는 노드는 pStart와 pEnd 사이에 존재하게 만들어준다.
	// 동적 할당!
	PNODE pStart;
	PNODE pEnd;
	int iSize;
}LIST, *PLIST;

static int InputInt() // static 없으면 obj 에러 발생! <- 두 cpp 파일에서 이 헤더 파일의 메소드를 갖다 쓰면, object를 중복 선언한 걸로 인식!
{
	int iInput;
	cin >> iInput;
	
	if (cin.fail()) // 입력 실패 시
	{
		cin.clear(); // 에러 버퍼 지워줌
		cin.ignore(1024, '\n'); // \n 부분까지 다 지워줌
		return INT_MAX; // INT_MAX belongs to <climits>
	}
	
	return iInput;
}

static void InputString(char* pString, int iSize)
{
	cin.clear(); // 에러 버퍼 지워줌 <- console에 input 값을 받을 때, 값을 입력하지 않았는 데 바로 다음 껄로 건너뛰는 거 방지
	cin.ignore(1024, '\n');
	cin.getline(pString, iSize-1); // 문자열의 마지막은 NULL
}

// List.cpp
// void InitList(PLIST pList);
// // void ClearList(PLIST pList);
// void DestroyList(PLIST pList);
// void Push_Back(PLIST pList); // 뒤에 추가하는 기능
// void Push_Front(PLIST pList); // 앞에 추가하는 기능
// void OutputStudent(const PSTUDENT pStudent);
// void Output(PLIST pList); // 정방향, 역방향 출력 <- 위의 enum 참고!
// void Search(PLIST pList);
// void Delete(PLIST pList);
// void Sort(PLIST pList);

void InitList(PLIST pList)
{
	pList->iSize = 0;
	
	pList->pStart = new NODE; // 동적 할당!
	pList->pEnd = new NODE;
	
	// 시작 노드의 다음 노드는 마지막 노드이다.
	pList->pStart->pNext = pList->pEnd; // pStart의 다음 노드는 pEnd
	
	// 마지막 노드의 이전 노드는 시작 노드이다.
	pList->pEnd->pPrev = pList->pStart; // pEnd의 이전 노드는 pStart
	
	// 마지막 노드의 다음 노드는 없으므로 NULL로 해준다.
	pList->pEnd->pNext = NULL; // pEnd의 다음 노드는 NULL
	
	// 시작 노드의 이전 노드는 없으므로 NULL로 해준다.
	pList->pStart->pPrev = NULL; // pStart의 이전 노드는 NULL
}

void DestroyList(PLIST pList)
{
	PNODE pNode = pList->pStart;
	
	while (pNode != NULL)
	{
		PNODE pNext = pNode->pNext;
		delete pNode;
		pNode = pNext;
	}
	
	pList->iSize = 0;
	pList->pStart = NULL;
	pList->pEnd = NULL;
}

void Push_Back(PLIST pList) // similar to Insert()
{
	system("clear");
	cout << "=============================== 학생 추가 ======================================" << endl;
	
	STUDENT tStudent = {};
	
	cout << "이름 : ";
	InputString(tStudent.strName, NAME_SIZE);
	
	cout << "학번 : ";
	tStudent.iNumber = InputInt();
	
	cout << "국어 : ";
	tStudent.iKor = InputInt();
	
	cout << "영어 : ";
	tStudent.iEng = InputInt();
	
	cout << "수학 : ";
	tStudent.iMath = InputInt();
	
	tStudent.iTotal = tStudent.iKor + tStudent.iEng + tStudent.iMath;
	tStudent.fAvg = tStudent.iTotal / 3.f;
	
	PNODE pNode = new NODE;
	
	pNode->tStudent = tStudent;
	
	// 새로 추가되는 노드는 End 노드의 이전 노드와 End 노드 사이에 추가해야 한다.
	// 그래서 pEnd의 prev 노드를 구해놓는다.
	PNODE pPrev = pList->pEnd->pPrev;
	
	// 그 후에 pEnd 노드 이전 노드의 다음으로 추가할 노드를 지정한다.
	pPrev->pNext = pNode;
	
	// 추가할 노드의 이전 노드로 End의 이전 노드를 지정한다. <- Double Linked!
	pNode->pPrev = pPrev;
	
	// 새로 추가할 노드의 다음 노드를 pEnd에 연결한다.
	pNode->pNext = pList->pEnd;
	
	// pEnd 노드의 이전 노드로 새로 추가할 노드를 지정한다. <- Double Linked!
	pList->pEnd->pPrev = pNode;
	
	++pList->iSize;
}

void Push_Front(PLIST pList)
{
	
}

void OutputStudent(const PSTUDENT pStudent) // 값을 바꿀 수 없다는 걸 이렇게 명시적으로 표현 <- 다른 프로그래머들도 쉽게 알 수 있게!
{
	cout << "이름 : " << pStudent->strName << "\t학번 : " << pStudent->iNumber << endl;
	cout << "국어 : " << pStudent->iKor << "\t영어 : " << pStudent->iEng << endl;
	cout << "수학 : " << pStudent->iMath << endl;
	cout << "총점 : " << pStudent->iTotal << "\t평균 : " << pStudent->fAvg << endl;
}

void Output(PLIST pList)
{
	int iMenu; // while문 안에서 선언하면 블록 밖에서 변수 사용 못 함!
	
	while (true)
	{
		system("clear");
		cout << "=============================== 학생 출력 ======================================" << endl;

		cout << "1. 정방향 출력" << endl;
		cout << "2. 역방향 출력" << endl;
		cout << "메뉴를 선택하세요 : ";
		iMenu = InputInt();
		
		if (iMenu > OT_NONE && iMenu <= OT_INVERSE)
			break;
	}
	
	PNODE pNode = NULL;
	
	switch (iMenu)
	{
		case OT_OUTPUT:
			// 추가되는 노드들은 start와 end 사이에 배치된다.
			// 그러므로 start의 다음 노드를 얻어온다.
			pNode = pList->pStart->pNext;
			
			// 노드가 End 노드와 같아지면 더 이상 출력할 노드가 없으므로 반복을 종료한다.
			while (pNode != pList->pEnd)
			{
				OutputStudent(&pNode->tStudent);
				pNode = pNode->pNext;
			}
			break;
		case OT_INVERSE:
			// 역방향으로 출력을 할 때는 end의 이전 노드를 얻어오고 계속 이전 노드로 진행한다.
			// start와 같아질 경우 반복을 종료한다.
			pNode = pList->pEnd->pPrev;
			
			// 역방향으로 들어가기 때문에 노드가 start와 같아지면 더 이상 출력할 노드가 없으므로 반복으로 종료한다.
			while (pNode != pList->pStart) // 싱글링크드리스트는 이게 불가능!(이전 노드를 가리키는 포인터가 없어서)
			{
				OutputStudent(&pNode->tStudent);
				pNode = pNode->pPrev;
			}
			break;
	}
	
	cout << "학생 수 : " << pList->iSize << endl;
	system("read –n1");
}

void Search(PLIST pList)
{
	system("clear");
	cout << "=============================== 학생 탐색 ======================================" << endl;
	
	cout << "탐색할 이름을 입력하세요 : ";
	char strName[NAME_SIZE] = {};
	InputString(strName, NAME_SIZE);
	
	PNODE pNode = pList->pStart->pNext;
	
	while (pNode != pList->pEnd)
	{
		if (strcmp(pNode->tStudent.strName, strName) == 0)
		{
			OutputStudent(&pNode->tStudent);
			system("read –n1");
			return;
		}
		
		pNode = pNode->pNext;
	}
	
	cout << "학생을 찾을 수 없습니다." << endl;
	system("read –n1");
}

void Delete(PLIST pList)
{
	system("clear");
	cout << "=============================== 학생 삭제 ======================================" << endl;
	
	cout << "삭제할 이름을 입력하세요 : ";
	char strName[NAME_SIZE] = {};
	InputString(strName, NAME_SIZE);
	
	PNODE pNode = pList->pStart->pNext;
	
	while (pNode != pList->pEnd)
	{
		if (strcmp(pNode->tStudent.strName, strName) == 0)
		{
			// 현재 지울 노드의 이전 노드의 다음은 현재 지울 노드로 되어 있다.
			// 그런데 지울 노드는 지워져야 하기 때문에 이전 노드의 다음 노드를 지울 노드의 다음 노드로 준다.
			// 다음 노드의 이전은 현재 노드인데 이전 노드로 준다.
			pNode->pPrev->pNext = pNode->pNext; // 이전 노드의 다음 노드를 현재 노드가 아닌, 그 다음 노드로 함!
			pNode->pNext->pPrev = pNode->pPrev; // 다음 노드의 이전 노드를 현재 노드가 아닌, 그 이전 노드로 함!
			delete pNode; // 그리고 현재 노드는 삭제!
			--pList->iSize;
			cout << strName << "학생을 삭제하였습니다." << endl;
			system("read –n1");
			return;
		}
		
		pNode = pNode->pNext;
	}
	
	cout << "삭제할 대상을 찾을 수 없습니다." << endl;
	system("read –n1");
}

void Sort(PLIST pList)
{
	system("clear");
	cout << "=============================== 학생 정렬 ======================================" << endl;
	cout << "1. 학번 기준" << endl;
	cout << "2. 평균 기준" << endl;
	cout << "메뉴를 선택하세요 : ";
	int iInput = InputInt();
	
	if (iInput <= ST_NONE || iInput > ST_AVG)
	{
		cout << "잘못 선택하였습니다." << endl;
		system("read –n1");
		return;
	}
	
	cout << endl;
	cout << "1. 오름차순" << endl;
	cout << "2. 내림차순" << endl;
	cout << "메뉴를 선택하세요 : ";
	int iOption = InputInt();
	
	if (iOption <= SO_NONE || iOption > SO_DESCRIVE)
	{
		cout << "잘못 선택하였습니다." << endl;
		system("read –n1");
		return;
	}
	
	PNODE pFirst = pList->pStart->pNext;
	PNODE pSecond = pFirst->pNext;
	
	// First는 End의 이전 노드와 같아지게 되면 더 이상 비교할 노드가 없으므로 종료한다.
	while (pFirst != pList->pEnd->pPrev) // pFirst가 pEnd의 이전 노드와 같아지면 비교할 노드가 없으니 종료
	{
		// Second는 무조건 First 노드 다음 노드부터 검사를 시작한다.
		pSecond = pFirst->pNext;
		
		// Second는 End 이전까지 반복해야 하므로 End가 아닐 동안만 반복한다.
		while (pSecond != pList->pEnd) // 하나의 노드에 대하여, 상대 노드가 pEnd 이전 노드가 될 때까지 비교
		{
			bool bSwap = false;
			
			switch (iInput)
			{
				case ST_NUMBER:
					switch (iOption)
					{
						case SO_CRIVE:
							if (pFirst->tStudent.iNumber > pSecond->tStudent.iNumber)
								bSwap = true; // 첫번째 노드의 학생 번호가 두번째 노드의 것보다 클 경우, 순서를 바꿔줌!
							break;
						case SO_DESCRIVE:
							if (pFirst->tStudent.iNumber < pSecond->tStudent.iNumber)
								bSwap = true; // 첫번째 노드의 학생 번호가 두번째 노드의 것보다 클 경우, 순서를 바꿔줌!
							break;
					}
				case ST_AVG:
					switch (iOption)
					{
						case SO_CRIVE:
							if (pFirst->tStudent.fAvg > pSecond->tStudent.fAvg)
								bSwap = true;
							break;
						case SO_DESCRIVE:
							if (pFirst->tStudent.fAvg < pSecond->tStudent.fAvg)
								bSwap = true;
							break;
					}
			}
			
			// bool 변수 bSwap이 true일 경우 두 노드를 바꿔야 한다는 것이다.
			if (bSwap)
			{
				// First 노드의 이전과 다음 노드를 저장한다.
				PNODE pFirstPrev = pFirst->pPrev;
				PNODE pFirstNext = pFirst->pNext;
				
				// Second 노드의 이전과 다음 노드를 저장한다.
				PNODE pSecondPrev = pSecond->pPrev;
				PNODE pSecondNext = pSecond->pNext;
				
				// 바꾸려는 두 노드가 붙어있는 경우
				if (pSecond == pFirstNext)
				{
					
				}
				
				// 떨어져 있는 경우
				else
				{
					
				}
				
				// 위에서 두 노드가 서로 바뀌었으므로, 연결되어 있던 pNext와 pPrev도 바꿔 주어야 한다.
				// 그래서 pFirstPrev 노드의 다음 노드로 바뀐 pFirst를 지정하고, 
				// 바뀐 pFirst의 이전 노드로 pFirstPrev 노드를 지정해준다.
				// 다음 노드들도 마찬가지로 교체해 주어야 한다.
				pFirstPrev->pNext = pSecond; // 링크 재설정!
				pSecond->pPrev = pFirstPrev;
				
				// 바꾸려는 두 노드가 붙어있지 않은 경우
				if (pSecond != pFirstNext)
				{
					pFirstNext->pPrev = pSecond;
					pSecond->pNext = pFirstNext;
					
					pSecondPrev->pNext = pFirst;
					pFirst->pPrev = pSecondPrev;
				}
				
				// 노드가 붙어있다면
				else
				{
					// swap?
					pSecond->pNext = pFirst;
					pFirst->pPrev = pSecond;
				}
				
				pSecondNext->pPrev = pFirst;
				pFirst->pNext = pSecondNext;
				
				// 두 노드를 바꿔준다.
				PNODE pTemp = pFirst;
				pFirst = pSecond;
				pSecond = pTemp;
			}
			
			pSecond = pSecond->pNext; // 다음 노드로 이동
		}
		
		pFirst = pFirst->pNext; // 다음 노드로 이동
	}
	
	cout << "정렬이 완료되었습니다." << endl;
	system("read –n1");
}
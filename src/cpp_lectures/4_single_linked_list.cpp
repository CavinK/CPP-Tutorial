#include <iostream>
#include <climits>
#include <cstring>

using namespace std;

// 열거체 <- like enumerate in Python
enum MAIN_MENU
{
	MM_NONE,
	MM_INSERT,
	MM_DELETE,
	MM_SEARCH,
	MM_OUTPUT,
	MM_EXIT
};

#define NAME_SIZE 32

// 구조체
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

/*
링크드리스트: 자료 구조의 한 종류이다. <- 목록(list)을 연결한다(link)
자료 구조란 데이터를 관리하는 방법을 말한다.
링크드리스트는 데이터 목록을 연결시켜서 접근할 수 있는 구조를 제공한다.
링크드리스트는 데이터를 저장하기 위한 노드라는 것이 존재한다.
각 노드의 특징은 다음 노드를 알 수 있게 된다.
(다음 노드의 메모리 주소를 저장한다는 의미이다.)

리스트는 선형 구조로 되어 있다. 
그렇기 때문에 배열처럼 특정 요소에 바로 접근이 불가능하다. <- 배열도 자료 구조의 한 종류!
무조건 앞에서부터 차례대로 타고 들어가야 한다.
노드를 새로 추가할 때는 노드를 생성하고 마지막 노드에 연결만 해주면 되기 떄문에 개수의 제한이 없다.
*/

// 리스트 노드를 만든다.
// 노드[데이터|다음노드주소]->노드[데이터|다음노드주소] <- 이렇게 구성!
typedef struct _tagNode
{
	STUDENT tStudent; // 데이터: 위의 구조체 STUDENT를 저장!
	_tagNode* pNext; // 다음노드주소 <- 자기 자신을 타입으로(_tagNode*) <- 다음 노드도 _tagNode 타입이기 때문!
}NODE, *PNODE;

// 리스트 구조체를 만들어준다.
typedef struct _tagList
{
	PNODE pStart; // 제일 첫 번째 노드의 주소
	PNODE pEnd; // 제일 마지막 노드의 주소
	int iSize; // 추가된 노드 개수
}LIST, *PLIST;

int InputInt()
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

void InputString(char* pString, int iSize)
{
	cin.clear(); // 에러 버퍼 지워줌 <- console에 input 값을 받을 때, 값을 입력하지 않았는 데 바로 다음 껄로 건너뛰는 거 방지
	cin.ignore(1024, '\n');
	cin.getline(pString, iSize-1); // 문자열의 마지막은 NULL
}

void InitList(PLIST pList)
{
	// 포인터는 가급적이면 초기화할 때 NULL(0)으로 초기화해두고 쓰는 것이 좋다.
	// 왜냐하면 0은 false, 0이 아닌 모든 수는 true이기 때문이다.
	// 초기화를 하지 않을 경우 쓰레기 값이 들어가 있는데, 이 쓰레기 값조차 true이다.
	pList->pStart = NULL; // 컴퓨터는 쓰레기 값과 실제 맞는 주소를 구분 못 함 => 명시적으로 NULL로 설정하여 초기화하는 것이 필요!
	pList->pEnd = NULL;
	pList->iSize = 0;
}

int OutputMenu()
{
	system("clear"); // 화면 지워주는 거 <- Windows: cls
	cout << "1. 학생추가" << endl;
	cout << "2. 학생삭제" << endl;
	cout << "3. 학생탐색" << endl;
	cout << "4. 학생출력" << endl;
	cout << "5. 종료" << endl;
	cout << "메뉴를 선택하세요 : ";
	int iInput = InputInt();
	
	if (iInput <= MM_NONE || iInput > MM_EXIT) // 1~5 이외의 값을 입력할 시
		return MM_NONE;
	
	return iInput;
}

void Insert(PLIST pList)
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
	
	// 추가할 리스트 노드를 생성한다.
	PNODE pNode = new NODE; // 동적 할당 <- 노드 하나를 heap에 동적 할당한 다음, 그 메모리 주소를 pNode가 가지고 있는 거
	
	// 현재 추가하는 노드는 가장 마지막에 추가될 것이기 때문에 다음 노드가 존재하지 않는다.
	// 그래서 다음 노드는 NULL로 초기화하고, 정보는 위에서 입력 받은 학생 정보를 주도록 한다.
	pNode->pNext = NULL;
	pNode->tStudent = tStudent;
	
	if (pList->pStart == NULL) // 아무 것도 추가 안 되어 있을 경우
		pList->pStart = pNode; // 시작 노드에 추가
	else
		pList->pEnd->pNext = pNode; // 마지막 노드의 다음 노드에 추가
	
	pList->pEnd = pNode; // 현재 노드를 마지막 노드로 설정!
	
	++pList->iSize; // iSize에 1 추가!
}

void ClearList(PLIST pList)
{
	PNODE pNode = pList->pStart; // 시작 노드의 주소
	
	while (pNode != NULL)
	{
		PNODE pNext = pNode->pNext; // 다음 노드의 주소
		delete pNode; // 현재의 시작 노드의 메모리 해제
		pNode = pNext; // 다음 노드를 시작 노드로 지정
	}
	
	// 초기화
	pList->pStart = NULL;
	pList->pEnd = NULL;
	pList->iSize = 0;
}

// const 포인터이기 때문에 가리키는 대상의 값을 변경할 수 없다.
// STUDENT를 인자로 받으면 구조체에 있는 원소들의 값들을 일일히 복사해서 느림!
// PSTUDENT로 주소를 인자로 넣으면 4바이트만 가져오기 때문에 훨씬 빨라짐 <- 대신 const를 써서 값을 변경하지 못 하게 함!
void OutputStudent(const PSTUDENT pStudent) // 값을 바꿀 수 없다는 걸 이렇게 명시적으로 표현 <- 다른 프로그래머들도 쉽게 알 수 있게!
{
	cout << "이름 : " << pStudent->strName << "\t학번 : " << pStudent->iNumber << endl;
	cout << "국어 : " << pStudent->iKor << "\t영어 : " << pStudent->iEng << endl;
	cout << "수학 : " << pStudent->iMath << endl;
	cout << "총점 : " << pStudent->iTotal << "\t평균 : " << pStudent->fAvg << endl;
}

void Output(PLIST pList)
{
	system("clear");
	cout << "=============================== 학생 출력 ======================================" << endl;
	
	PNODE pNode = pList->pStart;
	
	while (pNode != NULL)
	{
		OutputStudent(&pNode->tStudent);
		pNode = pNode->pNext;
	}
	
	cout << "학생 수 : " << pList->iSize << endl;
	
	system("read –n1"); // 콘솔 스크린 멈춰놓고 결과 확인 <- Windows: pause
}

void Search(PLIST pList)
{
	system("clear");
	cout << "=============================== 학생 탐색 ======================================" << endl;
	
	cout << "탐색할 이름을 입력하세요 : ";
	char strName[NAME_SIZE] = {};
	InputString(strName, NAME_SIZE);
	
	PNODE pNode = pList->pStart;
	
	while (pNode != NULL) // while문을 이용해 데이터를 전부 순회해서 이름에 해당되는 학생을 찾음 => 해당되는 값이 없으면 while문을 빠져나옴
	{
		if (strcmp(pNode->tStudent.strName, strName) == 0)
		{
			OutputStudent(&pNode->tStudent);
			system("read –n1");
			return;
		}
		
		pNode = pNode->pNext;
	}
	
	cout << "찾을 학생이 없습니다." << endl;
	system("read –n1");
}

void Delete(PLIST pList)
{
	system("clear");
	cout << "=============================== 학생 삭제 ======================================" << endl;
	
	cout << "삭제할 이름을 입력하세요 : ";
	char strName[NAME_SIZE] = {};
	InputString(strName, NAME_SIZE);
	
	PNODE pNode = pList->pStart;
	PNODE pPrev = NULL;
	
	while (pNode != NULL)
	{
		if (strcmp(pNode->tStudent.strName, strName) == 0)
		{
			// 지울 노드의 다음 노드를 얻어온다.
			PNODE pNext = pNode->pNext;
				
			// 만약 이전 노드가 NULL이라면, 제일 첫번째 노드를 지운다는 의미이다.
			if (pPrev == NULL)
			{
				delete pNode;
				pList->pStart = pNext; // 시작 노드를 지우고 그 다음 노드를 시작 노드로 지정
				
				if (pNext == NULL) // 노드가 하나 밖에 없을 경우
					pList->pEnd = NULL;
			}
			
			// 만약 이전 노드가 있을 경우에는, 이전 노드의 다음을 지운 노드의 다음 노드로 연결해준다.
			else
			{
				delete pNode;
				pPrev->pNext = pNext; // 이렇게 노드 간의 링크를 새로 연결해줘야!
				
				if (pNext == NULL) // 삭제해야 할 노드가 마지막 노드일 경우
					pList->pEnd = pPrev;
			}
			
			cout << strName << " 학생 삭제 완료" << endl;
			
			--pList->iSize; // 사이즈 1 감소
			system("read –n1");
			return;
		}
		
		// 해당 학생이 아니라면, 현재 노드가 이전 노드가 된다.
		pPrev = pNode;
		pNode = pNode->pNext; // 다음 노드로 이동해서 계속 값을 확인!(by while문)
	}
	
	// 그냥 while문을 빠져나올 경우(해당되는 값이 없을 경우)
	cout << "삭제할 학생을 찾을 수 없습니다." << endl;
	system("read –n1");
}

int main()
{
	// LIST 구조체 타입 변수를 생성한다.
	LIST tList;
	
	// InitList는 인자로 PLIST(_tagList*) 타입을 받으므로 주소를 넘겨준다.
	InitList(&tList); // 초기화
	
	while (true)
	{
		int iMenu = OutputMenu();
		
		if (iMenu == MM_EXIT)
			break;
		
		switch (iMenu)
		{
			case MM_INSERT:
				Insert(&tList);
				break;
			case MM_DELETE:
				Delete(&tList);
				break;
			case MM_SEARCH:
				Search(&tList);
				break;
			case MM_OUTPUT:
				Output(&tList);
				break;
		}
	}
	
	ClearList(&tList); // 노드 주소를 동적 할당 => 프로그램 종료 후 메모리 해제!
	
	return 0;
}
#include <iostream>
#include <climits>
#include <cstring>

// 사용자가 만든 헤더 파일을 포함시킬 때는 "" 안에 적어준다.
#include "List.h"

using namespace std;

enum MAIN_MENU
{
	MM_NONE,
	MM_INSERT,
	MM_DELETE,
	MM_SEARCH,
	MM_OUTPUT,
	MM_SORT,
	MM_EXIT
};

int OutputMenu()
{
	system("clear"); // 화면 지워주는 거 <- Windows: cls
	cout << "1. 학생추가" << endl;
	cout << "2. 학생삭제" << endl;
	cout << "3. 학생탐색" << endl;
	cout << "4. 학생출력" << endl;
	cout << "5. 학생정렬" << endl;
	cout << "6. 종료" << endl;
	cout << "메뉴를 선택하세요 : ";
	int iInput = InputInt();
	
	if (iInput <= MM_NONE || iInput > MM_EXIT) // 1~5 이외의 값을 입력할 시
		return MM_NONE;
	
	return iInput;
}

int main()
{
	LIST tList;
	
	InitList(&tList);
	
	while (true)
	{
		int iMenu = OutputMenu();
		
		if (iMenu == MM_EXIT)
			break;
		
		switch (iMenu)
		{
			case MM_INSERT:
				Push_Back(&tList);
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
			case MM_SORT:
				Sort(&tList);
				break;
		}
	}
	
	DestroyList(&tList);
	
	return 0;
}
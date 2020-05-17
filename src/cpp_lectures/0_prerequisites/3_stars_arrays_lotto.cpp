#include <iostream>
#include <time.h>

using namespace std;

int main() 
{
	/*
	*
	**
	***
	****
	*****
	*/

	for (int i = 1; i <= 5; ++i)
	{
		for (int j = 1; j <= i; ++j)
		{
			cout << "*";
		}
		cout << endl;
	}

	/*
	*****
	****
	***
	**
	*
	*/
	for (int i = 1; i <= 5; ++i)
	{
		for (int j = 5; j >= i; --j)
		{
			cout << "*";
		}
		cout << endl;
	}

	/*
	   *
	  ***
	 *****
	*******
	*/
	for (int i = 1; i <= 4; ++i)
	{
		for (int j = 1; j <= 7; ++j)
		{
			if (i + j >= 5 && j < i + 4)
			{
				cout << "*";
			}
			else
			{
				cout << " ";
			}
		}
		cout << endl;
	}

	// 공백: 3, 2, 1, 0		별: 1, 3, 5, 7
	for (int i = 0; i < 4; ++i)
	{
		for (int j = 0; j < 3 - i; ++j)
		{
			cout << " ";
		}

		for (int j = 0; j < i * 2 + 1; ++j)
		{
			cout << "*";
		}
		cout << endl;
	}

	/*
	   *
	  ***
	 *****
	*******
	 *****
	  ***
	   *
	*/
	int iLine = 7;
	int iCount = 0;

	for (int i = 0; i < iLine; ++i)
	{
		// 공백: 3, 2, 1, 0, 1, 2, 3
		// 별: 1, 3, 5, 7, 5, 3, 1

		iCount = i;

		// i값이 7줄 기준 4, 5, 6 즉 및의 삼각형을 구성할 때만 if문에 들어가게 된다.
		// i값이 4, 5, 6일 때는 iCount는 2, 1, 0이 된다.
		// 즉, 최종 i값은 0, 1, 2, 3, 2, 1, 0 이 된다.
		if (i > iLine / 2)
		{
			iCount = iLine - 1 - i;
		}

		for (int j = 0; j < 3 - iCount; ++j)
		{
			cout << " ";
		}

		for (int j = 0; j < iCount * 2 + 1; ++j)
		{
			cout << "*";
		}

		cout << endl;
	}

	/*
	do while 문: 반복문의 한 종류이다.
	형태: do {} while(조건식); 의 형태로 구성된다.
	while 문은 처음 진입부터 조건식을 체크하지만, 
	do while문은 처음 한 번은 무조건 동작이 되고 그 후에 조건식을 체크해서 true일 경우 반복해서 동작되는 반복문이다.
	*/
	int iNumber = 0;

	do
	{
		cout << iNumber << endl;
	} while (iNumber > 0);

	/*
	배열: 여러 개의 변수를 한 번에 생성해줄 수 있는 기능이다.
	형태: 변수타입 배열명[개수]; 의 형태로 선언할 수 있다.
	배열의 특징: 배열은 연속된 메모리 블럭에 공간이 할당된다. <- 별도의 변수에 값을 각각 할당하면 메모리에 드문드문 저장될 수도 있음
	배열은 인덱스를 이용해서 원하는 부분에 접근하여 값을 저장할 수 있다.
	인덱스는 0부터 개수-1 까지이다.
	즉, 10개라면 0 ~ 9 까지의 총 10개의 인덱스를 가지게 된다.
	*/

	// 배열 뿐만 아니라 일반 변수들도 선언을 하고 값을 초기화하지 않을 경우 쓰레기 값이 들어가게 된다.
	//int iArray[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10}; // 40byte(4x10) // 초기화 <- {} 사용!
	// 0 ~ 4번까지는 1, 2, 3, 4, 5 의 값이 들어가게 되고 나머지는 모두 0으로 초기화된다.
	//int iArray[10] = { 1, 2, 3, 4, 5 };
	
	// 비어있는 중괄호를 대입해줄 경우 모든 인덱스를 0으로 초기화한다.
	int iArray[10] = {}; // 배열 크기의 한계치 <- int로 표현할 수 있는 숫자까지!

	iArray[1] = 1234;

	for (int i = 0; i < 10; ++i)
	{
		cout << iArray[i] << endl;
	}
	//cout << iArray[5] << endl; // 쓰레기 값

	/*
	배열 개수를 2개 지정하면 2차원 배열이 된다.
	3개 지정하면 3차원 배열이 된다.
	2차원 배열의 개수는 앞의수 * 뒤의수 만큼 처리가 된다.
	아래는 10 * 10 개의 배열이 생성되는 것이다.
	*/
	int iArray2[10][10] = { {1, 2, 3}, {4, 5, 6} }; // 2차원 배열 <- 메모리에서는 선형으로 쭉 세팅됨!
	//int iArr[9999999999999999999999999999999999999999]; // 에러!

	for (int i = 0; i < 10; ++i)
	{
		for (int j = 0; j < 10; ++j)
		{
			cout << iArray2[i][j] << '\t';
		}
		cout << endl;
	}

	system("cls");

	srand((unsigned int)time(0));

	// Lotto Program
	int iLotto[45] = {};

	//for (int i = 0; i < 6; ++i)
	//{
	//	cout << rand() % 45 + 1 << endl; // 1 ~ 45 <- 중복될 확률이 존재!
	//}

	// Shuffle <- 1부터 45까지의 수를 배열에 전부 넣은 다음 섞어서 6개 뽑음!
	for (int i = 0; i < 45; ++i)
	{
		iLotto[i] = i + 1;
	}

	// Swap 알고리즘
	//int iNum1 = 1, iNum2 = 2, iNum3;
	//iNum3 = iNum1;
	//iNum1 = iNum2;
	//iNum2 = iNum3; // iNum1과 iNum2의 값이 서로 바뀜!

	int iTemp, idx1, idx2;
	// 100번 정도 골고루 섞어준다.
	for (int i = 0; i < 100; ++i)
	{
		idx1 = rand() % 45;
		idx2 = rand() % 45;

		iTemp = iLotto[idx1];
		iLotto[idx1] = iLotto[idx2];
		iLotto[idx2] = iTemp;
	}

	for (int i = 0; i < 6; ++i)
	{
		cout << iLotto[i] << "\t";
	}

	cout << "보너스 번호: " << iLotto[6] << endl;

	return 0;
}
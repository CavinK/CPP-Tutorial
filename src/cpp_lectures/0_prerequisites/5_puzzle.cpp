#include <iostream>
#include <time.h>

// console input output 헤더 파일이다.
// 콘솔창에서 입출력 하는 기능들을 제공해주는 헤더 파일이다.
#include <conio.h>

using namespace std;

int main()
{
	srand((unsigned int)time(0));

	int iNumber[25] = {};

	for (int i = 0; i < 24; ++i)
	{
		iNumber[i] = i + 1; // 1 ~ 24 까지 채워지고 마지막은 공백으로 남겨둠!
	}

	// 가장 마지막 칸은 공백으로 비워둔다.
	// 공백을 의미하는 값으로 특수한 값을 사용할 건데 INT_MAX 라는 값을 사용할 것이다.
	// INT_MAX는 이미 정의되어 있는 값으로, int로 표현할 수 있는 최대값이다.
	iNumber[24] = INT_MAX; // F12 눌러보기!

	// 별이 있는 위치를 저장할 변수를 만들어준다.
	int iStarIndex = 24; // 별이 움직일 때마다 별의 위치를 갱신시킴!

	// 마지막 공백을 제외하고 1 ~ 24 까지의 숫자만 섞어준다.
	// 죽 인덱스는 0 ~ 23번 인덱스 까지만 섞어준다,
	int iTemp, idx1, idx2;

	for (int i = 0; i < 100; ++i)
	{
		idx1 = rand() % 24;
		idx2 = rand() % 24;

		// Shuffle
		iTemp = iNumber[idx1];
		iNumber[idx1] = iNumber[idx2];
		iNumber[idx2] = iTemp;
	}

	/*for (int i = 0; i < 25; ++i)
	{
		cout << iNumber[i] << endl;
	}*/

	while (true)
	{
		system("cls");

		// i for문이 세로줄을 의미한다.
		for (int i = 0; i < 5; ++i)
		{
			// j for문이 가로 칸을 의미한다.
			for (int j = 0; j < 5; ++j)
			{
				// i가 0일 때 j는 0 ~ 4까지 반복한다.
				// 이 경우 0 * 5 + (0 ~ 4) 를 더하게 되서 인덱스가 0, 1, 2, 3, 4 가 나오게 된다.
				// i가 1일 때 j는 0 ~ 4까지 반복한다.
				// 이 경우 1 * 5 + (0 ~ 4) 를 더하게 되서 인덱스는 5, 6, 7, 8, 9 가 나오게 된다.
				// i가 2일 때 j는 0 ~ 4까지 반복한다.
				// 이 경우 2 * 5 + (0 ~ 4) 를 더하게 되서 인덱스는 10, 11, 12, 13, 14 가 나오게 된다.
				// i가 3일 때 j는 0 ~ 4까지 반복한다.
				// 이 경우 3 * 5 + (0 ~ 4) 를 더하게 되서 인덱스는 15, 16, 17, 18, 19 가 나오게 된다.
				// i가 4일 때 j는 0 ~ 4까지 반복한다.
				// 이 경우 4 * 5 + (0 ~ 4) 를 더하게 되서 인덱스는 20, 21, 22, 23, 24 가 나오게 된다.

				if (iNumber[i * 5 + j] == INT_MAX)
					cout << "*\t"; // 공백(INT_MAX)에 해당되는 부분은 *로 출력
				else
				{
					// 줄번호 * 가로개수 + 칸번호
					cout << iNumber[i * 5 + j] << "\t"; // 1차원 배열을 공식을 사용해서 2차원 배열처럼 사용되도록 만들었음!
				}
			}

			cout << endl;
		}

		// true로 주어서 먼저 모두 맞췄다 라고 가정해둔다.
		bool bWin = true;

		// 퍼즐을 맞추었는지 체크한다.
		for (int i = 0; i < 24; ++i)
		{
			if (iNumber[i] != i + 1)
			{
				bWin = false;
				break;
			}
		}

		if (bWin == true) // bWin이 true이면 위의 for문으로 들어가지 않았고, 제대로 정렬되었다는 뜻!
		{
			cout << "숫자를 모두 맞췄습니다." << endl;
			break; // while문에서 빠져나옴 => 게임 종료!
		}

		cout << "w: 위 s: 아래 a: 왼쪽 d: 오른쪽 q: 종료 : ";
		// _getch() 함수는 문자 1개를 입력 받는 함수이다.
		// 이 함수는 Enter를 치지 않더라도 문자를 누르는 순간 바로 그 문자를 반환하고 종료한다.
		char cInput = _getch(); // conio.h에 있는 기능을 이용해 Enter 키 안 눌러도 입력 가능하게 만듬!
		//cin >> cInput; // cin로 값을 받으면 Enter 키를 눌러줘야 값이 들어감! => w, s, a, d를 누르면 바로 입력 받도록 만들어야 함!

		if (cInput == 'q' || cInput == 'Q')
			break;

		switch (cInput)
		{
		case 'w':
		case 'W':
			// 가장 윗 줄일 때는 w를 눌러도 위로 올라가서는 안 된다. <- 잘못된 메모리 참조!
			if (iStarIndex > 4)
			{
				// 별이 있는 위치에 바로 위에 있는 값을 넣어준다.
				iNumber[iStarIndex] = iNumber[iStarIndex - 5]; // -5 하면 바로 위에 칸!
				// 위의 위치에 별을 넣어주어서 2개의 값을 서로 교체한다.
				iNumber[iStarIndex - 5] = INT_MAX; // swap
				// 별이 한 칸 위로 올라갔으므로 한 칸 위의 인덱스로 만들어준다.
				iStarIndex -= 5;
			}
			break;
		case 's':
		case 'S':
			if (iStarIndex < 20)
			{
				iNumber[iStarIndex] = iNumber[iStarIndex + 5];
				iNumber[iStarIndex + 5] = INT_MAX;
				iStarIndex += 5;
			}
			break;
		case 'a':
		case 'A':
			if (iStarIndex % 5 != 0)
			{
				iNumber[iStarIndex] = iNumber[iStarIndex - 1];
				iNumber[iStarIndex - 1] = INT_MAX;
				--iStarIndex;
			}
			break;
		case 'd':
		case 'D':
			if (iStarIndex % 5 != 4) // (iStarIndex + 1) % 5 != 0?
			{
				iNumber[iStarIndex] = iNumber[iStarIndex + 1];
				iNumber[iStarIndex + 1] = INT_MAX;
				++iStarIndex;
			}
			break;
		}
	}

	cout << endl << "게임을 종료합니다." << endl;

	return 0;
}
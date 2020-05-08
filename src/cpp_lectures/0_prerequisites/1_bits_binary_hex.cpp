#include <iostream>
#include <time.h>

using namespace std; 

int main() 
{
	// 상수: 변하지 않는 수 <- cf. 변수
	// 값을 한 번 지정해 놓으면 바꿀 수 없다.
	// 상수는 선언과 동시에 값을 지정해 두어야 한다.
	// 16진수 표기하는 방법: 앞에 0x를 붙임! <- 16진수 1자리가 2진수 4자리 => 16진수 1자리가 4비트를 차지(8자리가 32비트)
	const int iAttack = 0x00000001; // 헝가리안 표기법: 변수명 앞에 타입의 약자를 적음 // 0x00000001: 2진수로 그냥 1
	const int iArmor = 0x00000002; // 2진수로 10
	const int iHP = 0x00000004; // 2진수로 100
	const int iMP = 0x00000008; // 2진수로 1000
	// 비트 별로 의미를 부여! <- 제일 오른쪽 비트는 attack, 그 다음은 armor, 그 다음은 HP와 MP
	const int iCritical = 0x00000010; // 2진수로 10000
	// 이런 식으로 비트 단위로 32개까지 지정 가능!(32비트)

	// 2진수 <- 1 | 100 = 101 // 1 | 100 | 10000 = 10101
	int iBuf = iAttack | iHP | iCritical; // 버프: 일시적으로 생겼다가 해제됨 <- 변수로 지정!

	// 연산자 축약형: 연산자를 줄여서 사용할 수 있다.
	// 아래를 풀어서 쓰면 iBuf = iBuf ^ iHP;
	// 10101 ^ 100 = 10001 <- iBuf(10101)에서 HP(100)만 사라짐!
	iBuf ^= iHP; // ^: XOR

	// 10001 ^ 100 = 10101 <- XOR 2번 실행 => HP가 다시 생김! <- switch처럼 껐다 켰다 할 수 있음!!
	iBuf ^= iHP;

	// 10101 & 1 = 1 <- 0이 아님 => attack이 있다는 뜻
	cout << "Attack: " << (iBuf & iAttack) << endl;
	// 10101 & 10 = 0 <- armor 없다는 뜻
	cout << "Armor: " << (iBuf & iArmor) << endl;
	// 10101 & 100 = 100 <- HP
	cout << "HP: " << (iBuf & iHP) << endl;
	// 10101 & 1000 = 0
	cout << "MP: " << (iBuf & iMP) << endl;
	// 10101 & 10000 = 10000 <- critical
	cout << "Critical: " << (iBuf & iCritical) << endl;

	/*
	쉬프트 연산자: <<, >>
	값 대 값을 연산하여 값으로 나오게 된다.
	이 연산자 또한 2진수 단위의 연산을 하게 된다.
	<<: 빠른 곱하기 <- 일반적인 곱셈 연산보다 계산이 훨씬 빠름!(2의 n승 단위로 곱할 때는 쉬프트 연산자를 쓰는 게 나음)
	>>: 빠른 나누기
	
	20 << 2 <- 왼쪽으로 2칸 가라는 뜻(오른쪽에 0을 2개 붙이는 거!)
	20을 2진수로 변환한다.
	10100 => 1010000
	10진수로 80이 됨 <- 64 + 16
	20 << 2 = 80 <- 20에 2의 2승을 곱한 것과 같음!

	20 << 3 = 160 <- 왼쪽으로 한 칸 더 이동했는데 2배 증가! <- 20에 2의 3승을 곱한 것과 같음
	10100000 <- 10진수로 160(128 + 32)

	20 << 4 = 320 <- 2배 증가 <- 20에 2의 4승을 곱한 것과 같음!
	101000000

	20 >> 2 <- 오른쪽으로 2칸 가라는 뜻 <- 정수 대 정수 연산에서는 소수점이 자동적으로 짤림(둘 중 하나라도 실수면 실수)
	10100 => 101 <- 오른쪽에 있는 거 2개 지우는 거
	20 >> 2 = 5 <- 20에서 2의 2승을 나눈 것과 같음

	20 >> 3 = 2 <- 20에서 2의 3승을 나누고 얻은 몫과 같음
	10100 => 10
	*/
	int iHigh = 187;
	int iLow = 13560;

	int iNumber = iHigh; // 메모리가 적었던 시절에는 32비트를 상위 16비트, 하위 16비트로 나눠서 썼었음!

	// iNumber에는 187이 들어가 있다.
	// 이 값을 왼쪽 방향으로 16비트 이동시키면 상위 16비트에 값이 들어가게 된다.
	iNumber <<= 16; // 187 0x0000

	// 하위 16비트를 채운다.
	iNumber |= iLow; // OR 연산을 이용해서 0x0000 부분에 iLow 값을 집어넣음

	// High 값을 출력한다.
	cout << "High: " << (iNumber >> 16) << endl; // 오른쪽으로 16비트 지웠음!
	cout << "Low: " << (iNumber & 0x0000ffff) << endl; // f: 2진수로 1111 <- 0x0000ffff: 상위 16비트는 0으로 채우고, 하위 16비트는 1로 채웠음 <- AND 연산을 이용해서 하위 16비트에 있는 low 값을 출력!

	// 증감연산자: ++, -- 가 있다. 
	// 1 증가, 1 감소이다.
	iNumber = 10;

	// 전치
	++iNumber;

	// 후치
	iNumber++;

	cout << ++iNumber << endl; // 일단 증가부터 시킴
	cout << iNumber++ << endl; // 출력부터 하고 증가시킴
	cout << iNumber << endl;

	/*
	분기문에는 크게 2가지 종류가 있다.
	if문, switch문이 존재한다.

	if문: 조건을 체크해주는 기능이다.
	형태: if(조건식) {}(코드블럭)
	if문은 조건식이 true가 될 경우, 코드블럭 안의 코드가 동작된다.
	false일 경우에는 동작되지 않는다.
	*/
	if (true)
	{
		cout << "if문 조건이 true 입니다." << endl;
	}

	// 버프가 있는지 확인한다.
	if (iBuf & iAttack) // 0이면 false, 0이 아니면 true
	{
		cout << "Attack 버프가 있습니다." << endl;
	}

	// if문 아래에 들어갈 코드가 1줄일 경우 {}(코드블럭)을 생략할 수 있다.
	if ((iBuf & iArmor) != 0) // 연산자 우선 순위!
		cout << "Armor 버프가 있습니다." << endl;

	if (iBuf & iHP)
		cout << "HP 버프가 있습니다." << endl;

	if (iBuf & iMP)
		cout << "MP 버프가 있습니다." << endl;

	if (iBuf & iCritical)
		cout << "Critical 버프가 있습니다." << endl;

	/*
	else: if문과 반드시 같이 사용이 되어야 한다.
	if문 조건이 false일 경우 else가 있다면 else 구문 안의 코드가 동작된다.

	else if: if문과 반드시 같이 사용이 되어야 한다.
	if문 아래에 와야 하고 else보다는 위에 있어야 한다.
	else if는 자신의 위에 있는 조건식이 false일 경우 다음 else if의 조건식을 체크한다.
	else if는 몇 개든 사용이 가능하다.
	*/
	if (false)
		cout << "if문 조건이 true입니다." << endl;
	else
		cout << "if문 조건이 false입니다." << endl;

	cout << "숫자를 입력하세요 : ";
	cin >> iNumber;

	if (iNumber >= 10 && iNumber <= 20) // &&: 논리 연산자 // &: 비트 단위 논리 연산자(2진수 단위의 연산)
		cout << "10 ~ 20 사이의 숫자입니다." << endl;
	else if (iNumber >= 21 && iNumber <= 30)
		cout << "21 ~ 30 사이의 숫자입니다." << endl;
	else if (iNumber >= 31 && iNumber <= 40)
		cout << "31 ~ 40 사이의 숫자입니다." << endl;
	else
		cout << "그 외의 숫자입니다." << endl;

	// 난수 발생
	// 시간 별로 난수 테이블 발생 <- seed(시간 값)를 고정하면 난수 테이블도 고정!
	srand((unsigned int)time(0)); // 난수 테이블 발생 <- seed 값: time.h에서 가져다 씀!(time(0): 현재)

	cout << rand() << endl; // 임의의 값을 얻어옴
	cout << rand() << endl;
	cout << rand() << endl;
	cout << (rand() % 100) << endl; // 0 ~ 99 사이의 난수 <- % 연산자 활용!
	cout << (rand() % 101) << endl; // 0 ~ 100
	cout << (rand() % 101 + 100) << endl; // 100 ~ 200
	cout << (rand() % 10000 / 100.f) << endl; // 0 ~ 99.99 <- rand()는 10000 단위까지 밖에 안 나옴!

	int iUpgrade = 0;
	cout << "Upgrade 기본 수치를 입력하세요 : ";
	cin >> iUpgrade;

	// 강화 확률을 구한다.
	float fPercent = rand() % 10000 / 100.f;

	// 강화 확률: 
	// 업그레이드가 0 ~ 3 : 100% 성공
	// 4 ~ 6 : 40%
	// 7 ~ 9 : 10%
	// 10 ~ 13 : 1%
	// 14 ~ 15 : 0.01%
	cout << "Upgrade : " << iUpgrade << endl;
	cout << "Percent : " << fPercent << endl;

	if (iUpgrade <= 3)
		cout << "강화 성공" << endl;
	else if (iUpgrade >= 4 && iUpgrade <= 6)
	{
		if (fPercent < 40.f)
			cout << "강화 성공" << endl;
		else
			cout << "강화 실패" << endl;
	}
	else if (iUpgrade >= 7 && iUpgrade <= 9)
	{
		if (fPercent < 10.f)
			cout << "강화 성공" << endl;
		else
			cout << "강화 실패" << endl;
	}
	else if (iUpgrade >= 10 && iUpgrade <= 13)
	{
		if (fPercent < 1.f)
			cout << "강화 성공" << endl;
		else
			cout << "강화 실패" << endl;
	}
	else if (iUpgrade >= 14 && iUpgrade <= 15)
	{
		if (fPercent < .01f)
			cout << "강화 성공" << endl;
		else
			cout << "강화 실패" << endl;
	}

	return 0;
}
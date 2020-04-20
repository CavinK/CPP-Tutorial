#include <iostream>
#include <cstring>

using namespace std;

#define NAME_SIZE 32

/*
구조체 : 관련 있는 변수들을 모아서 하나의 "새로운 타입"을 만들어주는 기능이다.
사용자 정의 변수 타입이다.
형태 : struct 구조체명 {}; 의 형태로 구성된다.

배열과 구조체의 공통점
1. 데이터 집합이다.
2. 연속된 메모리 블록에 할당된다. 구조체 멤버들은 연속된 메모리 블록으로 잡히게 된다. <- 아래 구조체의 경우 56바이트

*/
struct _tagStudent
{
	char strName[NAME_SIZE]; // 32바이트 // define: 나중에 size를 변경할 때 이렇게 변수로 해놓으면 간편함!
	int iNumber; // 4바이트
	int iKor;
	int iEng;
	int iMath;
	int iTotal; 
	float fAvg; // 4바이트
};

int main()
{
	_tagStudent tStudent = {}; // 구조체 전체를 0으로 초기화! <- just like 배열 <- 초기화 안 하면 이상한 값들(쓰레기 값)이 들어감!
	_tagStudent tStudentArr[100] = {}; // Student 100명을 다 0으로 초기화 <- 52바이트 짜리 100개가 연속된 메모리 블록에 할당
	
	// 구조체 멤버에 접근할 때는 . 을 이용해서 접근하게 된다.
	tStudent.iKor = 100;
	
	// tStudent.strName = "abcdefgh"; // 에러!
	// 문자열을 배열에 넣어줄 때에는 단순 대입으로는 불가능하다.
	// strcpy_s() 라는 함수를 이용해서 문자열을 복사해 주어야 한다.
	// 이 함수는 오른쪽에 있는 문자열을 왼쪽으로 복사해준다.
	strcpy(tStudent.strName, "abcdefgh"); // string copy function which belongs to <cstring>
	
	// strcat() 함수는 문자열을 붙여주는 기능이다.
	// 오른쪽에 있는 문자열을 왼쪽에 붙여준다.
	// strName에는 위에서 abcdefgh를 저장해 두었기 때문에, 이 뒤에 오른쪽 문자열을 붙여서 만들어준다.
	strcat(tStudent.strName, "abcabc");
	
	// strcmp() 함수는 두 문자열을 비교하여, 같을 경우 0을 반환하고, 다를 경우 0이 아닌 값을 반환한다.
	strcpy(tStudent.strName, "Cavin");
	
	cout << "비교할 이름을 입력하세요 : ";
	char strName[NAME_SIZE] = {};
	cin >> strName;
	
	if (strcmp(tStudent.strName, strName) == 0)
	{
		cout << "학생을 찾았습니다." << endl;
	}
	else
	{
		cout << "찾는 학생이 없습니다." << endl;
	}
	
	// strtok(): string token function
	
	cout << "이름 길이 : " << strlen(tStudent.strName) << endl; // 문자열이 몇 바이트인 지 계산해서 결과를 보여주는 함수
	
	// 문자열의 끝은 항상 0(NULL)로 끝나야 한다.
	// 그런데 쓰레기 값이 들어가 있는 상태에서 아래처럼 각 배열 요소에 값을 넣어주게 되면 그 값이 출력되고
	// 넣어주지 않은 부분은 쓰레기 값으로 그대로 출력된다.
	// 왜나하면 출력할 때 문자열의 끝을 인식할 수 없기 때문이다.
	// 0이 들어가야 하는데 쓰레기 값이 들어가 있기 때문이다.
	// tStudent.strName[0] = 'a';
	// tStudent.strName[1] = 'a';
	// tStudent.strName[2] = 0; // 이렇게 끝에 0을 넣어줘야 쓰레기 값이 안 들어감! // strcpy() 함수는 끝에 0을 자동으로 채워줌!!
	
	cout << "이름 : " << tStudent.strName << endl;
	cout << "학번 : " << tStudent.iNumber << endl;
	cout << "국어 : " << tStudent.iKor << endl;
	cout << "영어 : " << tStudent.iEng << endl;
	cout << "수학 : " << tStudent.iMath << endl;
	cout << "총점 : " << tStudent.iTotal << endl;
	cout << "평균 : " << tStudent.fAvg << endl;
	
	return 0;
}
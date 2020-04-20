#include <iostream>

using namespace std;

// 구조체
struct _tagStudent
{
	int iKor;
	int iEng;
	int iMath;
	float fAvg;
};

int main()
{
	/*
	포인터: 가리키다. <- 다른 변수의 메모리 주소를 저장하고 있고, 이를 통해 값을 제어!
	일반 변수는 일반적인 값을 저장하게 되지만, 포인터 변수는 메모리 변수를 저장하게 된다. 
	모든 변수 타입은 포인터 타입을 선언할 수 있다. 
	int 변수의 주소는 int 포인터 변수에 저장을 해야 한다.
	포인터는 메모리 주소를 담아놓는 변수이기 때문에, x86으로 개발할 때는 무조건 4byte가 나온다.
	x64일 때는 8byte가 나온다.

	메모리 주소는 16진수 8자리로 표현!

	포인터는 자기 스스로 아무런 일도 할 수 없다.
	반드시 다른 변수의 메모리 주소를 가지고 있어야 일을 할 수 있는데,
	가지고 있는 그 메모리 주소에 접근해서 값을 제어할 수 있다.
	(기생충 같은 거! 메모리 주소를 갖고 있고 거기에 접근해서 값을 변경하는 기능 수행)

	형태: 변수 타입 *변수명; 의 형태로 선언한다.
	*/
	int iNumber = 100;
	// 변수 선언 시 *을 붙여주면 해당 타입의 포인터 변수가 선언된다.
	// 변수 앞에 &을 붙여주면, 해당 변수의 메모리 주소가 된다.
	// pNum은 iNumber 변수의 메모리 주소를 값으로 갖게 됐다.
	// 그러므로 pNum을 이용해서 iNumber의 값을 제어할 수 있게 된 것이다.
	int* pNum = &iNumber; // int 변수는 int 포인터의 메모리 주소를 가짐

	cout << sizeof(int*) << endl;
	cout << sizeof(char*) << endl; // 본래 char는 1byte인데 포인터 변수는 무조건 8byte(4byte)가 나옴!
	cout << sizeof(double*) << endl;
	
	// pNum을 이용해서 iNumber의 값을 제어해보자.
	// 역참조를 이용해서 값을 얻어오거나 변경할 수 있다.
	// 역참조는 포인터 변수 앞에 *을 붙이게 되면 역참조가 된다. <- 포인터 변수를 이용해 값을 가져옴!
	cout << *pNum << endl;
	*pNum = 1234; // 이런 식으로 iNumber 값을 바꿀 수 있음!(iNumber <- *pNum)
	
	cout << "iNumber Value : " << iNumber << endl;
	cout << "iNumber Address : " << &iNumber << endl;
	cout << "pNum Value : " << pNum << endl; // 위와 같음 // 이 주소를 통해 "역참조(*포인터명)" 해서 값을 수정
	cout << "pNum Address : " << &pNum << endl; // 포인터 변수의 주소
	
	
	
	/*
	포인터와 배열의 관계 : 배열명은 포인터다!!!
	배열명 자체가 해당 배열의 메모리에서의 시작점 주소를 의미한다.(iArray = &iArray[0])
	*/
	int iArray[10] = {1,2,3,4,5,6,7,8,9,10};
	
	cout << "Array Address : " << iArray << endl; // 시작점(iArray[0])의 메모리 주소!
	cout << "Array Address : " << &iArray[0] << endl; // 0번의 주소 <- 위와 같음!
	
	int* pArray = iArray; // 0번의 주소를 값으로 갖는 포인터
	
	cout << pArray[2] << endl; // 포인터 변수를 배열처럼 사용!(배열 내의 element 출력) <- pArray = &iArray[0] = iArray
	
	/*
	&iArray[0]을 값으로 갖는 포인터 생성 => &iArray[2]도 자동으로 생성!
	
	포인터 연산 : +, - 연산을 제공한다.
	++, --도 가능한데, 1을 증가하게 되면, 단순히 메모리 주소값이 1 증가하는 것이 아니다.
	int 포인터의 경우, int 타입의 메모리 주소를 갖게 되는데, 
	메모리 주소에 1을 더해주면 1 증가가 아닌, 해당 포인터 타입의 변수 타입 크기만큼 증가하게 된다.
	int 포인터이므로 int의 크기인 4만큼 값이 증가하게 되는 것이다.
	(ex. &iArray[0]: 3000번지 => &iArray[2]: 3008번지)
	*/
	cout << pArray << endl;
	cout << pArray + 2 << endl; // 주소가 8 증가!
	cout << *pArray << endl;
	cout << *(pArray + 2) << endl; // pArray[2]
	cout << *pArray + 100 << endl; // 본래 에러(out of range)가 나와야 하는데, 값(101)이 나옴! <- 연산자 우선 순위: iArray[0]을 역참조해서 1이 되고, 그 다음에 100을 더한 거!!
	cout << *(pArray + 100) << endl;
	
	
	
	// char 포인터
	char* pText = "테스트 문자열"; // 본래 char 배열로 해야 문자열이 나옴 <- const 속성(안 바꿀 문자열만 이렇게 사용)
	// pText[0] = 'a'; // 에러! <- 위의 문자열은 내부적으로 const(상수)로 고정되어 있어서, 이렇게 수정할 수 없음!
	// pText[1] = 'b';
	
	cout << pText << endl; // 근데 지금의 경우 그냥 문자열이 출력됨!(문자열을 char 배열로 생각할 것!)
	// 배열명도 메모리 주소라서 둘 다 메모리 주소를 의미! <- 큰따옴표 넣으면 내부적으로 메모리 주소로 인식
	cout << (int*)pText << endl; // 형 변환 후 문자열의 주소 출력
	
	pText = "abcd"; // 부분적으로 수정할 수는 없지만, 이런 식으로 가리키는 전체 문자열(char 배열) 자체는 바꿀 수 있음!	
	cout << pText << endl;
	cout << (int*)pText << endl;
	
	pText = "abcd";
	cout << (int*)pText << endl; // 같은 문자열을 쓸 때는 같은 주소!
	
	pText = "abcdefg";
	cout << (int*)pText << endl; // 다른 문자열로 바뀔 경우 주소가 바뀜!
	
	char str[8] = "abcdefg"; // 일반 char 배열 <- const 속성이 아니라 문자열 자체가 배열로 저장됨
	cout << str << endl;
	cout << (int*)str << endl; // 같은 문자열인데도 위와 주소가 다름! <- 이건 일반 배열이라서 배열 주소로 잡힘
	cout << (int*)&str[0] << endl;
	
	
	
	// 구조체 객체
	_tagStudent tStudent = {}; // 구조체 타입
	
	tStudent.iKor = 100;
	
	_tagStudent* pStudent = &tStudent; // 구조체도 일반 변수 같이 포인터를 통해 주소를 받아올 수 있음
	
	// 연산자 우선 순위 때문에 .을 먼저 인식하게 된다.
	// 메모리주소.은 잘못된 문법이다.
	// 그러므로 *pStudent를 괄호로 감싸준 후에 .을 이용해서 가리키는 대상의 멤버 변수에 접근해야 한다.
	(*pStudent).iKor = 50; // 포인터를 이용해 값 변경
	
	// 메모리주소-> 을 이용해서 가리키는 대상의 멤버에 접근할 수 있다.
	// 구조체포인터->원소 = 값
	pStudent->iKor = 80; // 위 코드와 같은 결과(간소화!)
	
	cout << tStudent.iKor << endl;
	
	
	
	// void: 타입이 없다. <- 변수 타입(리턴 타입)의 일종
	// void의 포인터 타입을 활용할 수 있다.
	// void* 변수를 선언하게 되면, 이 변수는 어떤 타입의 메모리 주소든 모두 저장 가능하다.
	// 단, 역참조가 불가능하고 메모리 주소만 저장 가능하다. <- 메모리 주소를 저장하는 버퍼로만 사용 가능
	void* pVoid = &iNumber; // 일반 변수의 메모리 주소 저장(변수 타입에 제한 받지 않음!)
	
	cout << "iNumber Address : " << pVoid << endl;
	// *pVoid = 10; // 에러! <- error: 'void*' is not a pointer-to-object type
	int* pConvert = (int*)pVoid; // void 포인터를 이용해 값을 제어하고 싶으면, 먼저 이렇게 형 변환을 해야 함!
	*pConvert = 10101010;
	*((int*)pVoid) = 9999; // 이런 식으로 void 포인터를 직접 타입 변환해서 값을 변경해도 됨! <- *pVoid => *((int*)pVoid)
	
	cout << iNumber << endl; // *pConvert를 이용해 iNumber 값을 변경!
	
	pVoid = &tStudent; // 포인터 변수 재활용 // 위의 구조체의 메모리 주소를 "int *pp == &tStudent;" 이런 식으로 저장하면 에러 발생!
	
	cout << "tStudent Address : " << pVoid << endl;
	
	
	
	// 이중 포인터: 포인터 변수의 주소를 저장하는 변수 <- 포인터의 포인터!
	int iNumber1 = 1111;
	iNumber = 2222;
	pNum = &iNumber;
	
	// *을 2개 붙인다.
	// 일반 포인터 변수가 일반 변수의 메모리 주소를 저장하는 변수라면, 이중 포인터는 포인터의 포인터이다.
	// 즉, 이중 포인터는 포인터 변수의 메모리 주소를 저장하는 포인터이다.
	int** ppNum = &pNum;
	
	*ppNum = &iNumber1; // *ppNum = pNum <- 이중 포인터의 역참조를 통해 pNum이 가리키는 일반 변수를 다른 일반 변수로 바꿀 수 있음!
	*pNum = 3333; // iNumber가 아닌, iNumber1의 값을 변경!
	
	cout << "iNumber1 : " << iNumber1 << endl;
	cout << "iNumber : " << iNumber << endl;
	cout << "iNumber Addr : " << &iNumber << endl;
	cout << "*pNum : " << *pNum << endl; // 역참조
	cout << "pNum Value : " << pNum << endl;
	cout << "pNum Addr : " << &pNum << endl;
	cout << "*ppNum : " << *ppNum << endl; // ppNum의 역참조 = pNum의 값 = iNumber의 주소
	cout << "**ppNum : " << **ppNum << endl; // ppNum의 역참조(pNum)의 역참조(iNumber)
	cout << "ppNum Value : " << ppNum << endl;
	cout << "ppNum Addr : " << &ppNum << endl;

	return 0;
}
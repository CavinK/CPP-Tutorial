#include <iostream>
#include <stdio.h>

using namespace std;

// pp는 main 함수 안에 있는 int* 타입의 p 변수의 주소(&p)를 가지게 된다.
void Test(int** pp) // 이중 포인터 함수(예시)
{
	*pp = new int; // 4바이트 짜리 동적 할당 => 메모리의 주소를 리턴!
}

int main()
{
	// 파일 입출력
	// C: 함수 기반
	// C++: 클래스 기반
	
	// int* p = NULL;
	// Test(&p); // p = new int; 와 같은 의미?
	
	FILE* pFile = NULL; // FILE*: std에서 제공되는 파일 포인터 <- 파일을 만들거나 읽어옴
	
	// 파일 생성
	// 1번 인자: 파일의 이중 포인터이다. <- 이중 포인터(&pFile)를 넣어주면, OS에서 내부적으로 파일 제어를 위한 객체를 만들어줌!
	// 2번 인자: 파일 경로이다. 파일이 생성되는 기준 경로는 현재 프로젝트가 있는 폴더 기준이다. 
	// 만약 실행 파일로 실행했을 경우에는 해당 exe 파일이 있는 경로를 기준으로 생성해준다.
	// 3번 인자: 파일 모드이다. 모드는 크게 2가지로 구분된다. 
	// 파일 읽기, 쓰기, 접근이 있고, 파일 형태, 텍스트 파일, 바이너리 파일 2가지 모드가 있어서 합쳐서 사용한다.
	// 텍스트 파일 vs 바이너리 파일(보안용!)
	// r: 읽기, w: 쓰기, a: 접근 // t: 텍스트 파일, b: 바이너리 파일
	fopen_s(&pFile, "hot.txt", "wt"); // fopen(): 옛날 거(call by value) // fopen_s(): 보안성 개선(call by address) <- Windows!
		
	if (pFile != NULL) // pFile == Null <- 메모리 주소가 없음 => 파일 만드는 것이 실패했음을 의미!
	{
		// fwrite, fread 2개의 함수가 제공된다.
		// fputs, fgets도 제공된다.
		char* pText = "abcd";
		// 1번 인자는 저장하고자 하는 값의 메모리 주소를 넣어준다. <- 버퍼(void 포인터?)
		// 2번 인자는 저장하고자 하는 값의 변수 타입의 메모리 크기를 넣어준다. <- 1바이트
		// 3번 인자는 저장하고자 하는 값의 개수를 넣어준다.
		// 4번 인자는 저장할 파일의 스트림을 넣어준다.
		fwrite(pText, 1, 4, pFile);
		
		fclose(pFile); // 파일을 제어하는 동안은 파일이 열려있는 상태 => 다 끝나고 닫아줘야!
		
		cout << "파일 만들기 성공" << endl;
	}
	
	// // 파일 읽기
	// fopen_s(&pFile, "hot.txt", "rt");
	
	// if (pFile)
	// {
	// 	char strText[5] = {};
		
	// 	fread(strText, 1, 4, pFile);
		
	// 	cout << strText << endl;
		
	// 	fclose(pFile);
		
	// 	cout << "파일 읽기 성공" << endl;
	// }
	
	return 0;
}
#include <iostream>

using namespace std;

void Test(int** pp) 
//pp는 main함수 안에 있는 int*타입의 p변수의 주소 가져옴
{
	*pp = new int;
}

int main()
{
	//int* p = NULL;
	//Test(&p);
	FILE* pFile = NULL;

	//1인자 : 파일의 이중포인터(메모리 주소 저장)
	//2		: 파일 경로. exe파일 위치
	//3		: 파일 모드(읽기, 쓰기, 접근, /형태)
	/*
	fopen_s(&pFile, "hot.txt", "wt");

	if (pFile != NULL)
		//만들기 실패
	{
		//fwritem, fread, fputs, fgets
		char* pText = "abcd";
		//1번인자 : 저장하고자 하는 값의 메모리 주소
		//2번인자 : 저장하고자 하는 값의 변수타입의 메모리 크기
		//3		: 저장하고자 하는 값의 개수
		//4		: 저장할 파일의 스트림(파일)
		fwrite(pText, 1, 4, pFile);
		fclose(pFile);
			//void 포인터의 특징 : 어떤게 들어올지 모를 때. 저장은 가능하지만 접근해서 작업은 불가
			cout << "파일만들기 성공" << endl;
	}
	*/
	//=======================파일 읽기=====================
	fopen_s(&pFile, "hot.txt", "rt");
	
	if (pFile)
	{
		char strText[5] = {};

		fread(strText, 1, 4, pFile);

		cout << strText << endl; 
		fclose(pFile);

	}

	return 0;

	 
		return 0;
}
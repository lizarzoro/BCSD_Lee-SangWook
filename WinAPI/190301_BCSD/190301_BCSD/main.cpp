#include <iostream>

using namespace std;

void Test(int** pp) 
//pp�� main�Լ� �ȿ� �ִ� int*Ÿ���� p������ �ּ� ������
{
	*pp = new int;
}

int main()
{
	//int* p = NULL;
	//Test(&p);
	FILE* pFile = NULL;

	//1���� : ������ ����������(�޸� �ּ� ����)
	//2		: ���� ���. exe���� ��ġ
	//3		: ���� ���(�б�, ����, ����, /����)
	/*
	fopen_s(&pFile, "hot.txt", "wt");

	if (pFile != NULL)
		//����� ����
	{
		//fwritem, fread, fputs, fgets
		char* pText = "abcd";
		//1������ : �����ϰ��� �ϴ� ���� �޸� �ּ�
		//2������ : �����ϰ��� �ϴ� ���� ����Ÿ���� �޸� ũ��
		//3		: �����ϰ��� �ϴ� ���� ����
		//4		: ������ ������ ��Ʈ��(����)
		fwrite(pText, 1, 4, pFile);
		fclose(pFile);
			//void �������� Ư¡ : ��� ������ �� ��. ������ ���������� �����ؼ� �۾��� �Ұ�
			cout << "���ϸ���� ����" << endl;
	}
	*/
	//=======================���� �б�=====================
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
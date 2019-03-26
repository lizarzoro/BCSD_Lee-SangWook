#include <iostream>

using namespace std;

template <typename T>
void OutputType()
{
	cout << "====== OutputData ======" << endl;
	cout << typeid(T).name() << endl;
}

template <typename T>
void OutputData(T data)
{
	cout << "====== OutputData ======" << endl;
	cout << typeid(T).name() << endl;
	cout << data << endl;
}

typedef struct _tagStudent
{

}STUDENT, *PSTUDENT;

class CCar
{
public:
	CCar()
	{

	}

	~CCar()
	{
		 
	}
};
int main()
{
	OutputType<int>();
	OutputType<float>();
	OutputType<STUDENT>();
	OutputType<CCar>();
	OutputData(10);
	OutputData(3.1);
	OutputData(382.383f);
	OutputData('a');
	OutputData("zzzzzzzzzz");


	return 0;
}
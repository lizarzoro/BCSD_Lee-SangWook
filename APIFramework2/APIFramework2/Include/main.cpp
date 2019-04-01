#include "Core.h"

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevinstance,
	_In_ LPWSTR IpCmdLinde,
	_In_ int nCmdShow)
{
	if (!CCore::GetInst()->Init(hInstance))
	{
		CCore::DestroyInst();
		return 0;
	}

	int iRev = CCore::GetInst()->Run();

	CCore::DestroyInst();

	return iRev;
}
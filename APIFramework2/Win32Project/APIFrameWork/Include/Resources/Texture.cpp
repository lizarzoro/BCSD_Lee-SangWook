#include "Texture.h"
#include "../Core/PathManager.h"


CTexture::CTexture() :
	m_hMemDC(NULL), 
	m_bColorKeyEnable(false),
	m_ColorKey(RGB(255, 0, 255)) {

}


CTexture::~CTexture() {

	SelectObject(m_hMemDC, m_hOldBitmap);

	DeleteObject(m_hBitmap);

	DeleteDC(m_hMemDC);
}

void CTexture::SetColorKey(unsigned char r, unsigned char g, unsigned char b) {
	m_ColorKey = RGB(r, g, b);
	m_bColorKeyEnable = true;
}

void CTexture::SetColorKey(COLORREF ColorKey) {
	m_ColorKey = ColorKey;
	m_bColorKeyEnable = true;
}

bool CTexture::LoadTexture(HINSTANCE hInst, HDC hDC,
	const string & strKey, const wchar_t * pFileName, 
	const string & strPathKey) {

	// 메모리 DC를 만들어준다.
	m_hMemDC = CreateCompatibleDC(hDC);

	// 전체 경로를 만들어준다.
	const wchar_t* pPath = GET_SINGLE(CPathManager)->FindPath(strPathKey);
	wstring strPath;

	if (pPath)
		strPath = pPath;

	strPath += pFileName;

	m_hBitmap = (HBITMAP)LoadImage(hInst, strPath.c_str(),
		IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);

	// 비트맵 도구를 DC에 지정. 기본으로 지정되어 있던 도구가 반환됨.
	m_hOldBitmap = (HBITMAP)SelectObject(m_hMemDC, m_hBitmap);

	GetObject(m_hBitmap, sizeof(m_tInfo), &m_tInfo);

	return true;
}

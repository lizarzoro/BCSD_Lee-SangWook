#include "Collider1.h"



CCollider1::CCollider1()
{

}

CCollider1::CCollider1(const CCollider1 & coll)
{
	*this = coll;
}


CCollider1::~CCollider1()
{
}

void CCollider1::Input(float fDeltaTime)
{
}

int CCollider1::Update(float fDeltaTime)
{
	return 0;
}

int CCollider1::LateUpdate(float fDeltaTime)
{
	return 0;
}

void CCollider1::Collision(float fDeltaTime)
{
}

void CCollider1::Render(HDC hDC, float fDeltaTime)
{
}

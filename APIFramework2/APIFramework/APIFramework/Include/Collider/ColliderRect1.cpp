#include "ColliderRect1.h"



CColliderRect1::CColliderRect1()
{
	m_eCollType = CT_RECT;
}

CColliderRect1::CColliderRect1(const CColliderRect1 & coll) :
	CCollider1(coll)
{
	//m_tInfo = coll.m_tInfo;
}



CColliderRect1::~CColliderRect1()
{
}

bool CColliderRect1::Init()
{
	return false;
}

void CColliderRect1::Input(float fDeltaTime)
{
}

int CColliderRect1::Update(float fDeltaTime)
{
	return 0;
}

int CColliderRect1::LateUpdate(float fDeltaTime)
{
	return 0;
}

bool CColliderRect1::Collision(CCollider1 * pDest)
{
	return false;
}

void CColliderRect1::Render(HDC hDC, float fDeltaTime)
{
}

CColliderRect1 * CColliderRect1::Clone()
{
	return new CColliderRect1(*this);
}

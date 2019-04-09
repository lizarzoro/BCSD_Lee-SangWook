#include "Player.h"
#include "../Core/Input.h"
#include "../Resources/Texture.h"
#include "Bullet.h"
#include "../Collider/ColliderRect.h"
#include "../Core/Camera.h"
#include "../Animation/Animation.h"
#include "../Scene/Scene.h"

CPlayer::CPlayer()
{
}

CPlayer::CPlayer(const CPlayer & player)	:
	CMoveObj(player)
{
}


CPlayer::~CPlayer()
{
}

void CPlayer::Fire()
{
	m_bAttack = true;

	CObj* pBullet = CObj::CreateCloneObj("Bullet", "PlayerBullet",
		m_pScene->GetSceneType(), m_pLayer);

	pBullet->AddCollisionFunction("Bullet", CS_STAY, (CBullet*)pBullet, &CBullet::Hit);

	// 오른쪽 가운데를 구한다.
	POSITION tPos;
	if (m_iDir == -1)
		tPos.x = GetLeft() - pBullet->GetSize().x * (1.f - pBullet->GetPivot().x);

	else
		tPos.x = GetRight() + pBullet->GetSize().x * pBullet->GetPivot().x;
	
	tPos.y = GetCenter().y;

	pBullet->SetPos(tPos);

	if (m_iDir == -1)
		((CMoveObj*)pBullet)->SetAngle(PI);

	SAFE_RELEASE(pBullet);
}

bool CPlayer::Init()
{
	SetPos(50.f, 50.f);
	SetSize(100.f, 100.f);
	SetSpeed(400.f);
	SetPivot(0.5f, 0.5f);
	SetImageOffset(0.f, 0.f);

	SetTexture("Player", L"D.trump.bmp");
	m_pTexture->SetColorKey(0, 255, 0);

	CColliderRect* pRC = AddCollider<CColliderRect>("Player");

	pRC->SetRect(-50.f, -50.f, 50.f, 50.f);
	pRC->AddCollisionFunction(CS_ENTER, this,
		&CPlayer::Hit);
	pRC->AddCollisionFunction(CS_STAY, this,
		&CPlayer::HitStay);
	
	SAFE_RELEASE(pRC);

	m_iHP = 1000;

	// 중력을 적용한다.
	SetPhysics(true);

	// 점프할 힘을 설정한다.
	SetForce(300.f);

	CAnimation* pAni = CreateAnimation("PlayerAnimation");

	// Atlas 방식으로 애니메이션 생성
	AddAnimationClip("IdleRight", AT_ATLAS, AO_LOOP, 0.6f, 3, 1,
		0, 0, 3, 1, 0.f, "PlayerIdleRight",
		L"Player/Idle/Right/Trump_Idle_Right.bmp");
	SetAnimationClipColorKey("IdleRight", 0, 255, 0);

	AddAnimationClip("IdleLeft", AT_ATLAS, AO_LOOP, 0.6f, 3, 1,
		0, 0, 3, 1, 0.f, "PlayerIdleLeft",
		L"Player/Idle/Left/Trump_Idle_Left.bmp");
	SetAnimationClipColorKey("IdleLeft", 0, 255, 0);

	AddAnimationClip("RunRight", AT_ATLAS, AO_ONCE_RETURN, 0.6f, 3, 1,
		0, 0, 3, 1, 0.f, "PlayerRunRight",
		L"Player/Run/Right/Trump_Run_Right.bmp");
	SetAnimationClipColorKey("RunRight", 0, 255, 0);

	AddAnimationClip("RunLeft", AT_ATLAS, AO_ONCE_RETURN, 0.6f, 3, 1,
		0, 0, 3, 1, 0.f, "PlayerRunLeft",
		L"Player/Run/Left/Trump_Run_Left.bmp");
	SetAnimationClipColorKey("RunLeft", 0, 255, 0);

	AddAnimationClip("NormalAttackRight", AT_ATLAS, AO_ONCE_RETURN, 1.f, 1, 1,
		0, 0, 1, 1, 0.f, "PlayerNormalAttackRight",
		L"Player/NormalAttack/Right/Trump_NormalAttack_Right.bmp");
	SetAnimationClipColorKey("NormalAttackRight", 0, 255, 0);

	// Frame 방식으로 애니메이션 생성
	vector<wstring> vecFileName;

	for (int i = 1; i <= 1; ++i)
	{
		wchar_t strFileName[MAX_PATH] = {};
		wsprintf(strFileName, L"Player/NormalAttack/Left/%d.bmp", i);
		vecFileName.push_back(strFileName);
	}

	AddAnimationClip("NormalAttackLeft", AT_FRAME, AO_ONCE_RETURN, 1.f, 1, 1,
		0, 0, 1, 1, 0.f, "PlayerNormalAttackLeft", vecFileName);
	SetAnimationClipColorKey("NormalAttackLeft", 0, 255, 0);

	SAFE_RELEASE(pAni);

	m_iDir = 1;

	return true;
}

void CPlayer::Input(float fDeltaTime)
{
	CMoveObj::Input(fDeltaTime);

	if (KEYPRESS("MoveLeft"))
	{
		MoveXFromSpeed(fDeltaTime, MD_BACK);
		if(!m_bAttack)
			m_pAnimation->ChangeClip("RunLeft");
		m_iDir = -1;
		m_pAnimation->SetDefaultClip("IdleLeft");
	}

	if (KEYPRESS("MoveRight"))
	{
		MoveXFromSpeed(fDeltaTime, MD_FRONT);
		if(!m_bAttack)
			m_pAnimation->ChangeClip("RunRight");
		m_iDir = 1;
		m_pAnimation->SetDefaultClip("IdleRight");
	}
	if (KEYDOWN("MoveFront"))
	{
		Jump();
		//MoveYFromSpeed(fDeltaTime, MD_BACK);
	}
	
	if (KEYPRESS("MoveBack"))
	{
		//MoveYFromSpeed(fDeltaTime, MD_FRONT);
	}

	if (KEYDOWN("Fire"))
	{
		Fire();

		if (m_iDir == -1)
			m_pAnimation->ChangeClip("NormalAttackLeft");

		else
			m_pAnimation->ChangeClip("NormalAttackRight");
	}

	if (KEYDOWN("Skill1"))
	{
		MessageBox(NULL, L"Skill1", L"Skill1", MB_OK);
	}
}

int CPlayer::Update(float fDeltaTime)
{
	CMoveObj::Update(fDeltaTime);

	if (m_bAttack && m_pAnimation->GetMotionEnd())
		m_bAttack = false;

	if (!m_bMove && !m_bAttack)
		m_pAnimation->ReturnClip();

	return 0;
}

int CPlayer::LateUpdate(float fDeltaTime)
{
	CMoveObj::LateUpdate(fDeltaTime);

	return 0;
}

void CPlayer::Collision(float fDeltaTime)
{
	CMoveObj::Collision(fDeltaTime);
}

void CPlayer::Render(HDC hDC, float fDeltaTime)
{
	CMoveObj::Render(hDC, fDeltaTime);
	wchar_t strHP[32] = {};
	wsprintf(strHP, L"HP : %d", m_iHP);
	POSITION tPos = m_tPos - m_tSize * m_tPivot;
	tPos -= GET_SINGLE(CCamera)->GetPos();
	TextOut(hDC, tPos.x, tPos.y, strHP, lstrlen(strHP));
	//Rectangle(hDC, m_tPos.x, m_tPos.y, m_tPos.x + m_tSize.x, m_tPos.y + m_tSize.y);
}

CPlayer * CPlayer::Clone()
{
	return new CPlayer(*this);
}

void CPlayer::Hit(CCollider * pSrc, CCollider * pDest, float fDeltaTime)
{
	if(pDest->GetObj()->GetTag() == "MinionBullet") {
		m_iHP -= 100;
	}

	else if (pDest->GetTag() == "StageColl")
	{
		ClearGravity();
		JumpEnd();
		m_tPos.y = pSrc->GetHitPoint().y - m_tPivot.y * m_tSize.y;
	}
}

void CPlayer::HitStay(CCollider * pSrc, CCollider * pDest, float fDeltaTime)
{
	if (pDest->GetTag() == "StageColl")
	{
		ClearGravity();
		JumpEnd();
		m_tPos.y = pSrc->GetHitPoint().y - m_tPivot.y * m_tSize.y;
	}
}
 
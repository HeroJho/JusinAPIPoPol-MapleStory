#include "stdafx.h"
#include "Monster.h"


CMonster::CMonster()
{
}


CMonster::~CMonster()
{
	Release();
}

void CMonster::Initialize(void)
{
	m_tInfo.fX = 550.f;
	m_tInfo.fY = 160.f;

	m_tInfo.fCX = 50.f;
	m_tInfo.fCY = 50.f;

	m_fSpeed = 1.f;

	m_pOldLine = nullptr;
	m_bJump = false;
	m_bOnAir = false;
	m_fValY = 0.f;
	m_fAirTime = 0.f;
}

int CMonster::Update(void)
{
	if (m_bDead)
		return OBJ_DEAD;


	m_tInfo.fX -= m_fSpeed;


	Update_Rect();

	return OBJ_NOEVENT;
}

void CMonster::Late_Update(void)
{
	Update_Gravity();
}

void CMonster::Render(HDC hDC)
{
	Rectangle(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
}

void CMonster::Release(void)
{
	
}

#include "stdafx.h"
#include "Monster.h"

#include "ScrollMgr.h"

CMonster::CMonster()
{
}

CMonster::~CMonster()
{
	Release();
}

void CMonster::Set_ID(MONSTERID _eID)
{
	m_eID = _eID;
}

void CMonster::Initialize(void)
{
	// �ݸ��� ũ��, �Ǻ� ����
	m_tInfo.fCCX = 50.f;
	m_tInfo.fCCY = 80.f;
	m_tColPivot.x = 0.f;
	m_tColPivot.y = -35.f;
	// �ؽ��� ũ�� ����
	m_tInfo.fTCX = 200.f;
	m_tInfo.fTCY = 200.f;


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
	int		iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int		iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

	Rectangle(hDC, m_tRect.left + iScrollX, m_tRect.top + iScrollY, m_tRect.right + iScrollX, m_tRect.bottom + iScrollY);
}

void CMonster::Release(void)
{
	
}

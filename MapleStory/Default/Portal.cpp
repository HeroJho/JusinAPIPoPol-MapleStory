#include "stdafx.h"
#include "Portal.h"

#include "ScrollMgr.h"

CPortal::CPortal()
{
}

CPortal::~CPortal()
{
	Release();
}

void CPortal::Initialize(void)
{
	// 콜리젼 크기, 피봇 설정
	m_tInfo.fCCX = 50.f;
	m_tInfo.fCCY = 80.f;
	m_tColPivot.x = 0.f;
	m_tColPivot.y = -35.f;
	// 텍스쳐 크기 설정
	m_tInfo.fTCX = 200.f;
	m_tInfo.fTCY = 200.f;

	m_fSpeed = 0.f;

	m_pOldLine = nullptr;
	m_bJump = false;
	m_bOnAir = false;
	m_fValY = 0.f;
	m_fAirTime = 0.f;
}

int CPortal::Update(void)
{
	if (m_bDead)
		return OBJ_DEAD;


	m_tInfo.fX -= m_fSpeed;


	Update_Rect();

	return OBJ_NOEVENT;
}

void CPortal::Late_Update(void)
{
	// Update_Gravity();
}

void CPortal::Render(HDC hDC)
{
	int		iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int		iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

	Rectangle(hDC, m_tRect.left + iScrollX, m_tRect.top + iScrollY, m_tRect.right + iScrollX, m_tRect.bottom + iScrollY);
}

void CPortal::Release(void)
{

}

void CPortal::OnCollision(CObj* _pOther)
{

}
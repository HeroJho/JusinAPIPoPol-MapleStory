#include "stdafx.h"
#include "Portal.h"

#include "ScrollMgr.h"
#include "BmpMgr.h"

CPortal::CPortal()
{
}

CPortal::~CPortal()
{
	Release();
}

void CPortal::Initialize(void)
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Map/Potal.bmp", L"Potal");
	Set_FrameKey(L"Potal");
	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 7;
	m_tFrame.iMotion = 0;
	m_tFrame.dwSpeed = 70.f;
	m_tFrame.dwTime = GetTickCount();



	// 콜리젼 크기, 피봇 설정
	m_tInfo.fCCX = 50.f;
	m_tInfo.fCCY = 80.f;
	m_tColPivot.x = 0.f;
	m_tColPivot.y = -35.f;
	// 텍스쳐 크기 설정
	m_tInfo.fTCX = 120.f;
	m_tInfo.fTCY = 230.f;

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


	Update_Rect();

	return OBJ_NOEVENT;
}

void CPortal::Late_Update(void)
{
	Move_Frame();
}

void CPortal::Render(HDC hDC)
{
	int		iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int		iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

	HDC		hMemDC = CBmpMgr::Get_Instance()->Find_Image(m_pFrameKey);

	GdiTransparentBlt(hDC,
		int(m_tTRect.left + iScrollX),
		int(m_tTRect.top - 100 + iScrollY),
		int(m_tInfo.fTCX),
		int(m_tInfo.fTCY),
		hMemDC,
		m_tFrame.iFrameStart * (int)m_tInfo.fTCX,
		m_tFrame.iMotion * (int)m_tInfo.fTCY,
		(int)m_tInfo.fTCX,
		(int)m_tInfo.fTCY,
		RGB(238, 241, 238));
}

void CPortal::Release(void)
{

}

void CPortal::OnCollision(CObj* _pOther)
{

}
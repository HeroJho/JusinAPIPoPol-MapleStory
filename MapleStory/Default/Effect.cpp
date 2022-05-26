#include "stdafx.h"
#include "Effect.h"


#include "ScrollMgr.h"
#include "BmpMgr.h"

CEffect::CEffect()
{
}

CEffect::~CEffect()
{
	Release();
}

void CEffect::Initialize(void)
{
	Set_FrameKey(L"Effect");
	m_bOnePlay = true;
	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 7;
	m_tFrame.iMotion = 0;
	m_tFrame.dwSpeed = (DWORD)40.f;
	m_tFrame.dwTime = (DWORD)GetTickCount64();


	// 콜리젼 크기, 피봇 설정
	m_tInfo.fCCX = 0.f;
	m_tInfo.fCCY = 0.f;
	m_tColPivot.x = (LONG)0.f;
	m_tColPivot.y = (LONG)0.f;
	// 텍스쳐 크기 설정
	m_tInfo.fTCX = 300.f;
	m_tInfo.fTCY = 300.f;

	Set_Stat(0, 0, 0);
	m_fSpeed = 0.f;

	m_bCanHit = false;
	m_CanHitCount = 0;
	m_CanHitMaxCount = 12;

	m_pOldLine = nullptr;
	m_bJump = false;
	m_bOnAir = false;
	m_fValY = 0.f;
	m_fAirTime = 0.f;

	m_fDeleteTime = 400.f;
	m_fOldSkillTime = GetTickCount64();
}

int CEffect::Update(void)
{
	if (m_bDead)
		return OBJ_DEAD;

	// 소멸 시간
	if (m_fOldSkillTime + m_fDeleteTime < GetTickCount64())
	{
		m_bDead = true;
	}

	Update_Rect();
	return OBJ_NOEVENT;
}

void CEffect::Late_Update(void)
{
	if (!m_bStayPlay)
		Move_Frame();
}

void CEffect::Render(HDC hDC)
{
	int		iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int		iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

	HDC		hMemDC = CBmpMgr::Get_Instance()->Find_Image(m_pFrameKey);

	GdiTransparentBlt(hDC, 						
		int(m_tTRect.left + iScrollX),			
		int(m_tTRect.top - 37 + iScrollY),
		int(m_tInfo.fTCX),						
		int(m_tInfo.fTCY),
		hMemDC,									
		m_tFrame.iFrameStart * (int)m_tInfo.fTCX,
		m_tFrame.iMotion * (int)m_tInfo.fTCY,
		(int)m_tInfo.fTCX,						
		(int)m_tInfo.fTCY,
		RGB(255, 0, 255));						

}

void CEffect::Release(void)
{
}

#include "stdafx.h"
#include "Dance2.h"
#include "BmpMgr.h"
#include "ScrollMgr.h"
#include "UIMgr.h"

CDance2::CDance2()
{
}

CDance2::~CDance2()
{
	Release();
}

void CDance2::Initialize(void)
{
	if(m_eDir == DIR_LEFT)
		m_pFrameKey = L"Dance2L";
	if(m_eDir == DIR_RIGHT)
		m_pFrameKey = L"Dance2R";

	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 15;
	m_tFrame.iMotion = 0;
	m_tFrame.dwSpeed = 60;
	m_tFrame.dwTime = (DWORD)GetTickCount64();


	// 콜리젼 크기, 피봇 설정
	m_tInfo.fCCX = 100.f;
	m_tInfo.fCCY = 100.f;
	m_tColPivot.x = (LONG)0.f;
	m_tColPivot.y = (LONG)0.f;
	// 텍스쳐 크기 설정
	m_tInfo.fTCX = 100.f;
	m_tInfo.fTCY = 100.f;

	m_pOldLine = nullptr;
	m_bJump = false;
	m_bOnAir = false;
	m_fValY = 0.f;
	m_fAirTime = 0.f;
	

	m_fTime = 2000.f;
	m_fOldTime = GetTickCount64();
}

int CDance2::Update(void)
{
	if (m_bDead)
		return OBJ_DEAD;

	if (!m_bJump)
	{
		if (m_eDir == DIR_LEFT)
		{
			m_tInfo.fX -= 0.5f;
		}
		else
		{
			m_tInfo.fX += 0.5f;
		}
	}


	if (m_fOldTime + m_fTime < GetTickCount64())
	{
		m_bJump = true;
	}


	Update_Rect();
	return OBJ_NOEVENT;
}

void CDance2::Late_Update(void)
{
	if (!m_bStayPlay)
		Move_Frame();
}

void CDance2::Render(HDC hDC)
{
	HDC		hMemDC = CBmpMgr::Get_Instance()->Find_Image(m_pFrameKey);

	GdiTransparentBlt(hDC,
		int(m_tTRect.left),
		int(m_tTRect.top - 37),
		int(m_tInfo.fTCX),
		int(m_tInfo.fTCY),
		hMemDC,
		m_tFrame.iFrameStart * (int)m_tInfo.fTCX,
		m_tFrame.iMotion * (int)m_tInfo.fTCY,
		(int)m_tInfo.fTCX,
		(int)m_tInfo.fTCY,
		RGB(255, 0, 255));

}

void CDance2::Release(void)
{
}

void CDance2::OnCollision(CObj* _pOther)
{

}

#include "stdafx.h"
#include "Screen_UI.h"
#include "BmpMgr.h"
#include "ScrollMgr.h"
#include "UIMgr.h"

CScreen_UI::CScreen_UI()
{
}

CScreen_UI::~CScreen_UI()
{
	Release();
}

void CScreen_UI::Initialize(void)
{
	m_bStart = false;

	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 19;
	m_tFrame.iMotion = 0;
	m_tFrame.dwSpeed = (DWORD)30.f;
	m_tFrame.dwTime = (DWORD)GetTickCount64();


	// 콜리젼 크기, 피봇 설정
	m_tInfo.fCCX = 0.f;
	m_tInfo.fCCY = 0.f;
	m_tColPivot.x = (LONG)0.f;
	m_tColPivot.y = (LONG)0.f;
	// 텍스쳐 크기 설정
	m_tInfo.fTCX = 1280.f;
	m_tInfo.fTCY = 720.f;


	m_fSpeed = 0.f;

	m_pOldLine = nullptr;
	m_bJump = false;
	m_bOnAir = false;
	m_fValY = 0.f;
	m_fAirTime = 0.f;
}

int CScreen_UI::Update(void)
{
	if (m_bDead)
		return OBJ_DEAD;

	Update_Rect();

	if (!m_bStart)
		return OBJ_NOEVENT;

	Move_Frame();


	return OBJ_NOEVENT;
}

void CScreen_UI::Late_Update(void)
{

}

void CScreen_UI::Render(HDC hDC)
{
	if (!m_bStart)
		return;


	HDC		hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"Screen");


	GdiTransparentBlt(hDC, 						
		int(0),			
		int(0),
		int(m_tInfo.fTCX),						
		int(m_tInfo.fTCY),
		hMemDC,									
		m_tFrame.iFrameStart * (int)m_tInfo.fTCX,
		m_tFrame.iMotion * (int)m_tInfo.fTCY,
		(int)m_tInfo.fTCX,						
		(int)m_tInfo.fTCY,
		RGB(255, 0, 255));						

}

void CScreen_UI::Release(void)
{
}

void CScreen_UI::OnCollision(CObj* _pOther)
{

}


void CScreen_UI::Move_Frame(void)
{
	if (m_tFrame.dwTime + m_tFrame.dwSpeed < GetTickCount64())
	{
		m_tFrame.iFrameStart++;

		m_tFrame.dwTime = (DWORD)GetTickCount64();

		if (m_tFrame.iFrameStart > m_tFrame.iFrameEnd)
		{
			m_tFrame.iFrameStart = m_tFrame.iFrameEnd;
		}
	}
}



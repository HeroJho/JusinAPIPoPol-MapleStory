#include "stdafx.h"
#include "Screen1_UI.h"
#include "BmpMgr.h"
#include "ScrollMgr.h"
#include "UIMgr.h"

CScreen1_UI::CScreen1_UI()
{
}

CScreen1_UI::~CScreen1_UI()
{
	Release();
}


void CScreen1_UI::Initialize(void)
{
	m_bStart = false;

	Set_FrameKey(L"domiOpen");
	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 17;
	m_tFrame.iMotion = 0;
	m_tFrame.dwSpeed = (DWORD)100.f;
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

int CScreen1_UI::Update(void)
{
	if (m_bDead)
		return OBJ_DEAD;

	Update_Rect();

	if (!m_bStart)
		return OBJ_NOEVENT;

	Move_Frame();


	return OBJ_NOEVENT;
}

void CScreen1_UI::Late_Update(void)
{

}

void CScreen1_UI::Render(HDC hDC)
{
	if (!m_bStart)
		return;

	HDC		hMemDC = CBmpMgr::Get_Instance()->Find_Image(m_pFrameKey);

	

	GdiTransparentBlt(hDC,
		int(0 - 1),
		int(0),
		int(m_tInfo.fTCX),
		int(m_tInfo.fTCY),
		hMemDC,
		m_tFrame.iFrameStart * (int)m_tInfo.fTCX,
		m_tFrame.iMotion * (int)m_tInfo.fTCY,
		(int)m_tInfo.fTCX,
		(int)m_tInfo.fTCY,
		RGB(255, 0, 255));

	if (m_pFrameKey == L"domiOpen" && m_tFrame.iFrameStart == 20)
	{
		m_bStart = false;
	}
}

void CScreen1_UI::Release(void)
{
}

void CScreen1_UI::OnCollision(CObj* _pOther)
{

}





void CScreen1_UI::Move_Frame(void)
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


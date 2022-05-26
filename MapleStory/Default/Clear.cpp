#include "stdafx.h"
#include "Clear.h"

#include "BmpMgr.h"
#include "ScrollMgr.h"
#include "UIMgr.h"

CClear::CClear()
{
}

CClear::~CClear()
{
	Release();
}

void CClear::Initialize(void)
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Clear.bmp", L"Clear");
	Set_FrameKey(L"Clear");
	// m_bStayPlay = true;
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
	m_tInfo.fTCX = 700.f;
	m_tInfo.fTCY = 200.f;

	m_pOldLine = nullptr;
	m_bJump = false;
	m_bOnAir = false;
	m_fValY = 0.f;
	m_fAirTime = 0.f;
}

int CClear::Update(void)
{
	if (m_bDead)
		return OBJ_DEAD;


	Update_Rect();
	return OBJ_NOEVENT;
}

void CClear::Late_Update(void)
{
	if (!m_bStayPlay)
		Move_Frame();
}

void CClear::Render(HDC hDC)
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

void CClear::Release(void)
{
}

void CClear::OnCollision(CObj* _pOther)
{

}

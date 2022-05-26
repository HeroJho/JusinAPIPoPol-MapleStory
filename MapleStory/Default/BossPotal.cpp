#include "stdafx.h"
#include "BossPotal.h"
#include "ScrollMgr.h"
#include "BmpMgr.h"

CBossPotal::CBossPotal()
{
}

CBossPotal::~CBossPotal()
{
	Release();
}

void CBossPotal::Initialize(void)
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Map/BossPotal.bmp", L"BossPotal");
	Set_FrameKey(L"BossPotal");
	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 7;
	m_tFrame.iMotion = 0;
	m_tFrame.dwSpeed = 70.f;
	m_tFrame.dwTime = GetTickCount64();


	// 콜리젼 크기, 피봇 설정
	m_tInfo.fCCX = 50.f;
	m_tInfo.fCCY = 80.f;
	m_tColPivot.x = 0.f;
	m_tColPivot.y = -35.f;
	// 텍스쳐 크기 설정
	m_tInfo.fTCX = 150.f;
	m_tInfo.fTCY = 190.f;

	m_fSpeed = 0.f;

	m_pOldLine = nullptr;
	m_bJump = false;
	m_bOnAir = false;
	m_fValY = 0.f;
	m_fAirTime = 0.f;
}

int CBossPotal::Update(void)
{
	if (m_bDead)
		return OBJ_DEAD;


	Update_Rect();

	return OBJ_NOEVENT;
}

void CBossPotal::Late_Update(void)
{
	Move_Frame();
}

void CBossPotal::Render(HDC hDC)
{
	int		iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int		iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

	HDC		hMemDC = CBmpMgr::Get_Instance()->Find_Image(m_pFrameKey);

	GdiTransparentBlt(hDC,
		int(m_tTRect.left + iScrollX),
		int(m_tTRect.top - 80 + iScrollY),
		int(m_tInfo.fTCX),
		int(m_tInfo.fTCY),
		hMemDC,
		m_tFrame.iFrameStart * (int)m_tInfo.fTCX,
		m_tFrame.iMotion * (int)m_tInfo.fTCY,
		(int)m_tInfo.fTCX,
		(int)m_tInfo.fTCY,
		RGB(255, 0, 255));
}

void CBossPotal::Release(void)
{

}

void CBossPotal::OnCollision(CObj* _pOther)
{

}
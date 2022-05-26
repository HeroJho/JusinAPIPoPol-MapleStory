#include "stdafx.h"
#include "Maya.h"
#include "EventMgr.h"
#include "ScrollMgr.h"
#include "BmpMgr.h"
#include "SpawnMgr.h"

#include "Money.h"
#include "AbstractFactory.h"
#include "ObjMgr.h"
#include "Player.h"
#include "UIMgr.h"
#include "KeyMgr.h"

CMaya::CMaya()
	: m_fOldTime(GetTickCount64())
	, m_fRandTime(0.f)
{

}

CMaya::~CMaya()
{
	Release();
}

void CMaya::Initialize(void)
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Npc/Maya.bmp", L"Maya");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Npc/Maya.bmp", L"Maya");
	Set_FrameKey(L"Maya");
	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 0;
	m_tFrame.iMotion = 0;
	m_tFrame.dwSpeed = 500.f;
	m_tFrame.dwTime = GetTickCount64();

	m_eCurState = IDLE;

	// 콜리젼 크기, 피봇 설정
	m_tInfo.fCCX = 300.f;
	m_tInfo.fCCY = 25.f;
	m_tColPivot.x = 0.f;
	m_tColPivot.y = -10.f;
	// 텍스쳐 크기 설정
	m_tInfo.fTCX = 100.f;
	m_tInfo.fTCY = 100.f;

	m_fSpeed = 0.0f;

	m_bDecPlayer = false;
	m_pOldLine = nullptr;
	m_bJump = false;
	m_bOnAir = false;
	m_fValY = 0.f;
	m_fAirTime = 0.f;
}

int CMaya::Update(void)
{
	if (m_bDead)
		return OBJ_DEAD;

	if (!m_bDecPlayer)
		CUIMgr::Get_Instance()->CloseShop();
	m_bDecPlayer = false;


	switch (m_eCurState)
	{
	case IDLE:
		Update_Idle();
		break;
	}

	Update_Rect();

	return OBJ_NOEVENT;
}

void CMaya::Late_Update(void)
{
	Update_Gravity();

	if (!m_bStayPlay)
	{
		Motion_Change();
		Move_Frame();
	}
}

void CMaya::Render(HDC hDC)
{
	int		iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int		iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

	HDC		hMemDC = CBmpMgr::Get_Instance()->Find_Image(m_pFrameKey);

	GdiTransparentBlt(hDC, 									// 복사 받을, 최종적으로 그림을 그릴 DC
		int(m_tTRect.left + iScrollX),					// 2,3 인자 :  복사받을 위치 X, Y
		int(m_tTRect.top - 35 + iScrollY),
		int(m_tInfo.fTCX),								// 4,5 인자 : 복사받을 가로, 세로 길이
		int(m_tInfo.fTCY),
		hMemDC,											// 비트맵을 가지고 있는 DC
		m_tFrame.iFrameStart * (int)m_tInfo.fTCX,		// 비트맵 출력 시작 좌표, X,Y
		m_tFrame.iMotion * (int)m_tInfo.fTCY,
		(int)m_tInfo.fTCX,								// 복사할 비트맵의 가로, 세로 길이
		(int)m_tInfo.fTCY,
		RGB(255, 0, 255));								// 제거하고자 하는 색상

	LOGFONT m_labelFontInfo{};
	m_labelFontInfo.lfHeight = 13;
	m_labelFontInfo.lfWidth = 7;
	m_labelFontInfo.lfCharSet = HANGEUL_CHARSET;
	HFONT textFont, oldFont;
	textFont = CreateFontIndirect(&m_labelFontInfo);
	oldFont = (HFONT)SelectObject(hDC, textFont);

	SetBkMode(hDC, OPAQUE);
	SetBkColor(hDC, RGB(0, 0, 0));
	SetTextColor(hDC, RGB(255, 255, 255));
	TCHAR lpOut[1024];
	wsprintf(lpOut, TEXT("마야"));
	TextOut(hDC, m_tTRect.left + iScrollX + 37, m_tTRect.top - 83 + iScrollY + 145, lpOut, lstrlen(lpOut));

	SelectObject(hDC, oldFont);
	DeleteObject(textFont);
}

void CMaya::Release(void)
{

}

void CMaya::SetCurState(STATE _eState, DIRECTION _eDir)
{
	if (_eDir == DIR_LEFT)
		m_pFrameKey = L"Maya";
	else
		m_pFrameKey = L"Maya";

	m_eDir = _eDir;
	m_eCurState = _eState;
}


void CMaya::Update_Idle()
{
}


void CMaya::OnCollision(CObj* _pOther)
{
	if (_pOther->Get_Tag() == "Player")
	{
		m_bDecPlayer = true;

		if (CKeyMgr::Get_Instance()->Key_Down(VK_SHIFT))
		{
			CUIMgr::Get_Instance()->OpenShop();
		}
	}
}


void CMaya::Motion_Change(void)
{
	if (m_ePreState != m_eCurState)
	{
		switch (m_eCurState)
		{
		case IDLE:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 0;
			m_tFrame.iMotion = 0;
			m_tFrame.dwSpeed = 500.f;
			m_tFrame.dwTime = GetTickCount64();
			break;
		}

		m_ePreState = m_eCurState;
	}
}
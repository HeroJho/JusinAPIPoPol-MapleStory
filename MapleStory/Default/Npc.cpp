#include "stdafx.h"
#include "Npc.h"
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
#include "QuestMgr.h"


CNpc::CNpc()
	: m_fOldTime(GetTickCount64())
	, m_fRandTime(0.f)
{

}

CNpc::~CNpc()
{
	Release();
}

void CNpc::Initialize(void)
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Npc/JangL.bmp", L"JangL");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Npc/JangR.bmp", L"JangR");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/UI/QuestMark.bmp", L"QuestMark");
	Set_FrameKey(L"JangL");
	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 4;
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

	m_fSpeed = 0.4f;

	m_bDecPlayer = false;
	m_pOldLine = nullptr;
	m_bJump = false;
	m_bOnAir = false;
	m_fValY = 0.f;
	m_fAirTime = 0.f;

	m_pQ = new CQuest;
	m_pQ->Initialize();
	m_pQ->Set_Target(this);

	m_bMark = false;
}

int CNpc::Update(void)
{
	if (m_bDead)
		return OBJ_DEAD;

	m_pQ->Update();

	if (!m_bDecPlayer)
		ChooseRandStat();

	m_bDecPlayer = false;


	switch (m_eCurState)
	{
	case IDLE:
		Update_Idle();
		break;
	case MOVE:
		Update_Walk();
		break;
	}

	Update_Rect();

	return OBJ_NOEVENT;
}

void CNpc::Late_Update(void)
{
	Update_Gravity();

	if (!m_bStayPlay)
	{
		Motion_Change();
		Move_Frame();
	}

	m_pQ->Late_Update();
}

void CNpc::Render(HDC hDC)
{
	int		iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int		iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

	HDC		hMemDC = CBmpMgr::Get_Instance()->Find_Image(m_pFrameKey);
	GdiTransparentBlt(hDC, 						
		int(m_tTRect.left + iScrollX),			
		int(m_tTRect.top - 29 + iScrollY),
		int(m_tInfo.fTCX),						
		int(m_tInfo.fTCY),
		hMemDC,									
		m_tFrame.iFrameStart * (int)m_tInfo.fTCX,
		m_tFrame.iMotion * (int)m_tInfo.fTCY,
		(int)m_tInfo.fTCX,						
		(int)m_tInfo.fTCY,
		RGB(255, 0, 255));						

	if (m_bMark)
	{
		HDC		hMemMarkDC = CBmpMgr::Get_Instance()->Find_Image(L"QuestMark");
		GdiTransparentBlt(hDC,
			int(m_tTRect.left - 20 + iScrollX),
			int(m_tTRect.top - 120 + iScrollY),
			126,
			91,
			hMemMarkDC,
			0,
			0,
			126,
			91,
			RGB(0, 255, 0));
	}

	switch (CQuestMgr::Get_Instance()->GetQuest())
	{
		case Stay1:
		case Stay2:
		case Stay3:
			m_pQ->SetIdle();
			break;
		case Q1:
		case Q2:
		case Q3:
			m_pQ->SetMove();
			break;
		case CQ1:
		case CQ2:
			m_pQ->SetEnd();
			break;
	}

	if(!m_bMark)
		m_pQ->Render(hDC);


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
	wsprintf(lpOut, TEXT("장로 현수"));
	TextOut(hDC, m_tTRect.left + iScrollX + 19, m_tTRect.top - 83 + iScrollY + 145, lpOut, lstrlen(lpOut));

	SelectObject(hDC, oldFont);
	DeleteObject(textFont);
}

void CNpc::Release(void)
{
	Safe_Delete(m_pQ);
	m_pQ = nullptr;
}

void CNpc::SetCurState(STATE _eState, DIRECTION _eDir)
{
	if (_eDir == DIR_LEFT)
		m_pFrameKey = L"JangL";
	else
		m_pFrameKey = L"JangR";

	m_eDir = _eDir;
	m_eCurState = _eState;
}

void CNpc::ChooseRandStat()
{
	if (m_fOldTime + m_fRandTime < GetTickCount64())
	{
		m_fRandTime = CEventMgr::Get_Instance()->GetRandomNum_Int(4000, 10000);
		STATE eRandStat = STATE(CEventMgr::Get_Instance()->GetRandomNum_Int(0, 1));
		DIRECTION eRandDir = DIRECTION(CEventMgr::Get_Instance()->GetRandomNum_Int(0, 1));

		SetCurState(eRandStat, eRandDir);

		m_fOldTime = GetTickCount64();
	}
}


void CNpc::Update_Idle()
{
}

void CNpc::Update_Walk()
{
	if (m_eDir == DIR_LEFT)
		m_tInfo.fX -= m_fSpeed;
	else if (m_eDir == DIR_RIGHT)
		m_tInfo.fX += m_fSpeed;
}


void CNpc::OnCollision(CObj* _pOther)
{
	if (_pOther->Get_Tag() == "Player")
	{
		m_bDecPlayer = true;
		DIRECTION eDir = _pOther->Get_Dir();
		if (eDir == DIR_LEFT)
			eDir = DIR_RIGHT;
		else
			eDir = DIR_LEFT;

		SetCurState(IDLE, eDir);

		if (CKeyMgr::Get_Instance()->Key_Down(VK_SHIFT))
		{
			// TODO: 대화창
			CUIMgr::Get_Instance()->OpenCommunity();
		}
	}
	else if (_pOther->Get_Tag() == "Block")
	{
		if (m_eDir == DIR_LEFT)
			SetCurState(m_eCurState, DIR_RIGHT);
		else if (m_eDir == DIR_RIGHT)
			SetCurState(m_eCurState, DIR_LEFT);
	}
}


void CNpc::Motion_Change(void)
{
	if (m_ePreState != m_eCurState)
	{
		switch (m_eCurState)
		{
		case IDLE:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 4;
			m_tFrame.iMotion = 0;
			m_tFrame.dwSpeed = 500.f;
			m_tFrame.dwTime = GetTickCount64();
			break;

		case MOVE:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 3;
			m_tFrame.iMotion = 1;
			m_tFrame.dwSpeed = 100.f;
			m_tFrame.dwTime = GetTickCount64();
			break;
		}

		m_ePreState = m_eCurState;
	}
}
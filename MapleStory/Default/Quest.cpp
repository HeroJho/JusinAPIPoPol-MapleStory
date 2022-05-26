#include "stdafx.h"
#include "Quest.h"
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

CQuest::CQuest()
{

}

CQuest::~CQuest()
{
	Release();
}

void CQuest::Initialize(void)
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/UI/QuestIcon.bmp", L"QuestIcon");
	Set_FrameKey(L"QuestIcon");
	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 0;
	m_tFrame.iMotion = 0;
	m_tFrame.dwSpeed = 500.f;
	m_tFrame.dwTime = GetTickCount64();

	m_eCurState = IDLE;

	// �ݸ��� ũ��, �Ǻ� ����
	m_tInfo.fCCX = 0.f;
	m_tInfo.fCCY = 0.f;
	m_tColPivot.x = 0.f;
	m_tColPivot.y = 0.f;
	// �ؽ��� ũ�� ����
	m_tInfo.fTCX = 50.f;
	m_tInfo.fTCY = 50.f;

	m_fSpeed = 0.0f;

	m_pOldLine = nullptr;
	m_bJump = false;
	m_bOnAir = false;
	m_fValY = 0.f;
	m_fAirTime = 0.f;
}

int CQuest::Update(void)
{
	if (m_bDead)
		return OBJ_DEAD;

	m_tInfo.fX = m_pTarget->Get_Info().fX + 15;
	m_tInfo.fY = m_pTarget->Get_Info().fY - 63.f;

	Update_Rect();

	return OBJ_NOEVENT;
}

void CQuest::Late_Update(void)
{
	if (!m_bStayPlay)
	{
		Motion_Change();
		Move_Frame();
	}
}

void CQuest::Render(HDC hDC)
{
	int		iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int		iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

	HDC		hMemDC = CBmpMgr::Get_Instance()->Find_Image(m_pFrameKey);

	GdiTransparentBlt(hDC, 									// ���� ����, ���������� �׸��� �׸� DC
		int(m_tTRect.left + iScrollX),					// 2,3 ���� :  ������� ��ġ X, Y
		int(m_tTRect.top - 35 + iScrollY),
		int(m_tInfo.fTCX),								// 4,5 ���� : ������� ����, ���� ����
		int(m_tInfo.fTCY),
		hMemDC,											// ��Ʈ���� ������ �ִ� DC
		m_tFrame.iFrameStart * (int)m_tInfo.fTCX,		// ��Ʈ�� ��� ���� ��ǥ, X,Y
		m_tFrame.iMotion * (int)m_tInfo.fTCY,
		(int)m_tInfo.fTCX,								// ������ ��Ʈ���� ����, ���� ����
		(int)m_tInfo.fTCY,
		RGB(255, 0, 255));								// �����ϰ��� �ϴ� ����
}

void CQuest::Release(void)
{

}

void CQuest::SetCurState(STATE _eState, DIRECTION _eDir)
{
	m_eDir = _eDir;
	m_eCurState = _eState;
}

void CQuest::OnCollision(CObj* _pOther)
{

}


void CQuest::Motion_Change(void)
{
	if (m_ePreState != m_eCurState)
	{
		switch (m_eCurState)
		{
		case IDLE:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 7;
			m_tFrame.iMotion = 0;
			m_tFrame.dwSpeed = 100.f;
			m_tFrame.dwTime = GetTickCount64();
			break;
		case MOVE:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 3;
			m_tFrame.iMotion = 1;
			m_tFrame.dwSpeed = 100.f;
			m_tFrame.dwTime = GetTickCount64();
			break;
		case END:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 7;
			m_tFrame.iMotion = 2;
			m_tFrame.dwSpeed = 100.f;
			m_tFrame.dwTime = GetTickCount64();
			break;
		}

		m_ePreState = m_eCurState;
	}
}
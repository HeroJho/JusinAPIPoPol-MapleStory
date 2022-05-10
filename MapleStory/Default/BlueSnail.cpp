#include "stdafx.h"
#include "BlueSnail.h"

#include "EventMgr.h"
#include "ScrollMgr.h"
#include "BmpMgr.h"
#include "SpawnMgr.h"

CBlueSnail::CBlueSnail()
	: m_fOldTime(GetTickCount64())
	, m_fRandTime(0.f)
{

}

CBlueSnail::~CBlueSnail()
{
	Release();
}

void CBlueSnail::Initialize(void)
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Monster/DarPang_1/DarPang_1L.bmp", L"DarPang_1L");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Monster/DarPang_1/DarPang_1R.bmp", L"DarPang_1R");
	Set_FrameKey(L"DarPang_1L");
	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 0;
	m_tFrame.iMotion = 0;
	m_tFrame.dwSpeed = 1000.f;
	m_tFrame.dwTime = GetTickCount();


	m_fOldHitTime = 0.f;
	m_fHitTime = 1000.f;
	m_fOldChaseTime = 0.f;
	m_fChaseTime = 10000.f;
	m_fOldDeadTime = 0.f;
	m_fDeadTime = 2000.f;


	// 콜리젼 크기, 피봇 설정
	m_tInfo.fCCX = 25.f;
	m_tInfo.fCCY = 25.f;
	m_tColPivot.x = 0.f;
	m_tColPivot.y = -10.f;
	// 텍스쳐 크기 설정
	m_tInfo.fTCX = 100.f;
	m_tInfo.fTCY = 100.f;

	Set_Stat(50, 1);
	m_bCanHit = true;

	m_fSpeed = 0.4f;

	m_pOldLine = nullptr;
	m_bJump = false;
	m_bOnAir = false;
	m_fValY = 0.f;
	m_fAirTime = 0.f;
}

int CBlueSnail::Update(void)
{
	if (m_bDead)
		return OBJ_DEAD;

	if(m_eCurState != CHASE && m_eCurState != DEAD)
		ChooseRandStat();

	switch (m_eCurState)
	{
	case CMonster::IDLE:
		Update_Idle();
		break;
	case CMonster::WALK:
		Update_Walk();
		break;
	case CMonster::CHASE:
		Update_Chase();
		break;
	case CMonster::HIT:
		Update_Hit();
		break;
	case CMonster::DEAD:
		Update_Dead();
		break;
	}

	Update_Rect();

	return OBJ_NOEVENT;
}

void CBlueSnail::Late_Update(void)
{
	Update_Gravity();

	if (!m_bStayPlay)
	{
		Motion_Change();
		Move_Frame();
	}
}

void CBlueSnail::Render(HDC hDC)
{
	int		iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int		iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

	HDC		hMemDC = CBmpMgr::Get_Instance()->Find_Image(m_pFrameKey);

	GdiTransparentBlt(hDC, 									// 복사 받을, 최종적으로 그림을 그릴 DC
		int(m_tTRect.left + iScrollX),					// 2,3 인자 :  복사받을 위치 X, Y
		int(m_tTRect.top - 17 + iScrollY),
		int(m_tInfo.fTCX),								// 4,5 인자 : 복사받을 가로, 세로 길이
		int(m_tInfo.fTCY),
		hMemDC,											// 비트맵을 가지고 있는 DC
		m_tFrame.iFrameStart * (int)m_tInfo.fTCX,		// 비트맵 출력 시작 좌표, X,Y
		m_tFrame.iMotion * (int)m_tInfo.fTCY,
		(int)m_tInfo.fTCX,								// 복사할 비트맵의 가로, 세로 길이
		(int)m_tInfo.fTCY,
		RGB(255, 0, 255));								// 제거하고자 하는 색상
}

void CBlueSnail::Release(void)
{

}

void CBlueSnail::SetCurState(STATE _eState, DIRECTION _eDir)
{
	if (_eDir == DIR_LEFT)
		m_pFrameKey = L"DarPang_1L";
	else
		m_pFrameKey = L"DarPang_1R";

	m_eDir = _eDir;
	m_eCurState = _eState;
}

void CBlueSnail::ChooseRandStat()
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

void CBlueSnail::Update_Idle()
{
}

void CBlueSnail::Update_Walk()
{
	if (m_eDir == DIR_LEFT)
		m_tInfo.fX -= m_fSpeed;
	else if (m_eDir == DIR_RIGHT)
		m_tInfo.fX += m_fSpeed;
}

void CBlueSnail::Update_Chase()
{
	if (!m_pTarget)
	{
		SetCurState(IDLE, m_eDir);
		return;
	}

	if (m_fOldChaseTime + m_fChaseTime < GetTickCount64())
	{
		SetCurState(IDLE, m_eDir);
		return;
	}


	float fChaseDir = m_pTarget->Get_Info().fX - m_tInfo.fX;

	if (10.f < fChaseDir)
	{
		SetCurState(CHASE, DIR_RIGHT);
		m_tInfo.fX += m_fSpeed + 0.2f;
	}
	else if(-10.f > fChaseDir)
	{
		SetCurState(CHASE, DIR_LEFT);
		m_tInfo.fX -= m_fSpeed + 0.2f;
	}
	else
	{
		SetCurState(IDLE, m_eDir);
	}
}

void CBlueSnail::Update_Hit()
{
	if (m_fOldHitTime + m_fHitTime < GetTickCount64())
	{
		SetCurState(CHASE, m_eDir);
		m_fOldChaseTime = GetTickCount64();
	}
}

void CBlueSnail::Update_Dead()
{
	if (m_fOldDeadTime + m_fDeadTime < GetTickCount64())
	{
		m_bDead = true;
	}
}

void CBlueSnail::OnHit(CObj* _pOther)
{
	m_tStat.iHp -=  _pOther->Get_Stat().iAt;
	if (m_tStat.iHp <= 0.f)
	{
		SetCurState(DEAD, m_eDir);
		m_fOldDeadTime = GetTickCount64();
		m_bCanHit = false;
		CSpawnMgr::Get_Instance()->DecreaseCount();
		return;
	}

	m_fOldHitTime = GetTickCount64();

	DIRECTION eDir = _pOther->Get_Target()->Get_Dir();
	m_pTarget = _pOther->Get_Target();
	if (eDir == DIR_LEFT)
	{
		SetCurState(HIT, DIR_RIGHT);
		m_tInfo.fX -= 12.f;
	}
	else
	{
		SetCurState(HIT, DIR_LEFT);
		m_tInfo.fX += 12.f;
	}
}


void CBlueSnail::OnCollision(CObj* _pOther)
{
	if (_pOther->Get_Tag() == "Player")
	{
		if(m_bCanHit)
			_pOther->OnHit(this);
	}
	else if (_pOther->Get_Tag() == "Block")
	{
		if (m_eDir == DIR_LEFT)
			SetCurState(m_eCurState, DIR_RIGHT);
		else if (m_eDir == DIR_RIGHT)
			SetCurState(m_eCurState, DIR_LEFT);
	}
}

void CBlueSnail::OnePlayEnd(void)
{
	m_tFrame.iFrameStart = 2;
	m_tFrame.iFrameEnd = 2;
	m_tFrame.iMotion = 1;
	m_tFrame.dwSpeed = 200;
	m_tFrame.dwTime = GetTickCount();
}

void CBlueSnail::Motion_Change(void)
{
	if (m_ePreState != m_eCurState)
	{
		switch (m_eCurState)
		{
		case IDLE:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 0;
			m_tFrame.iMotion = 0;
			m_tFrame.dwSpeed = 1000.f;
			m_tFrame.dwTime = GetTickCount();
			break;

		case WALK:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 3;
			m_tFrame.iMotion = 2;
			m_tFrame.dwSpeed = 100.f;
			m_tFrame.dwTime = GetTickCount();
			break;

		case CHASE:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 3;
			m_tFrame.iMotion = 2;
			m_tFrame.dwSpeed = 50.f;
			m_tFrame.dwTime = GetTickCount();
			break;

		case HIT:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 0;
			m_tFrame.iMotion = 3;
			m_tFrame.dwSpeed = 200;
			m_tFrame.dwTime = GetTickCount();
			break;

		case DEAD:
			m_bOnePlay = true;
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 2;
			m_tFrame.iMotion = 1;
			m_tFrame.dwSpeed = 200;
			m_tFrame.dwTime = GetTickCount();
			break;
		}

		m_ePreState = m_eCurState;
	}
}